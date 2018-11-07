/*
Copyright 2018 Joaquín Cuéllar

This file is part of GSResolver.

GSResolver is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GSResolver is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GSResolver.  If not, see <https://www.gnu.org/licenses/>.
*/

#include"methodsManager.h"

int method::load()
{
  int ret = -1;  

  is_loaded=1;
  // load the symbols
  create_pluginInstance = (create_t*) dlsym(my_so, "create");
  const char* dlsym_error = dlerror();
  if (dlsym_error) {
    std::cerr << "ERR: Cannot load symbol create: " << dlsym_error << '\n';
    is_loaded= 0;
  }
  destroy_pluginInstance = (destroy_t*) dlsym(my_so, "destroy");
  dlsym_error = dlerror();
  if (dlsym_error) {
    std::cerr << "ERR: Cannot load symbol destroy: " << dlsym_error << '\n';
    is_loaded= 0;
  }    
    
  if(is_loaded)
    ret = 0;
  return ret;
}

void method::refresh_info()
{
  if(is_loaded)
    {
      resolvMethod* myMethod = create_pluginInstance();
      name = myMethod->retMethodName();
      description = myMethod->retMethodDescription();
    }
  else
    {
      description = "N/A";
    }
}

void methodsManager::searchFolders(std::vector <std::string>  & folders)
{
  folders.clear();
  const char* PATH = "./methods";

  DIR *dir = opendir(PATH);

  struct dirent *entry = readdir(dir);

  while (entry != NULL)
    {
      if (entry->d_type == DT_DIR)
	if(strlen(entry->d_name) > 4)
	  {
	    if(!(entry->d_name[strlen(entry->d_name) - 1] == '.' && entry->d_name[strlen(entry->d_name) - 2] == '.' && entry->d_name[strlen(entry->d_name) - 3] == '/'))
	      {
		if(!(entry->d_name[strlen(entry->d_name) - 1] == '.' && entry->d_name[strlen(entry->d_name) - 2] == '/'))	
		  folders.push_back(entry->d_name);
	      }
	  }
      entry = readdir(dir);
    }

  closedir(dir);

  return;
}
void methodsManager::freePlugins()
{
  if(num_methods)
    {
      for(int i=num_methods-1; i >= 0;i--)
	{
	  delete my_methods[i];
	}
      free(my_methods);      
    }
  
  return;
}

void methodsManager::loadPlugins()
{
  std::vector <std::string> pluginList;
  std::vector <std::string>::iterator iter; 

  freePlugins();
  num_methods = 0;
  searchFolders(pluginList);
  if(pluginList.size())
    {
      my_methods = new method*[pluginList.size()];
      int i=0;
      for(iter = pluginList.begin(); iter != pluginList.end(); ++iter)
	{
	  std::string path = "./methods/";
	  path += *iter;
	  path += "/";
	  path += *iter;
	  path += ".so";
	  my_methods[i] = new method();
	  my_methods[i]->set_path(path);
	  my_methods[i]->my_so =  dlopen(path.c_str(), RTLD_LAZY);
	  my_methods[i]->set_name(*iter);

	  std::string status = "Plugin correctly loaded";
	  if (!my_methods[i]->my_so)
	    {
	      status = "ERR: Cannot load library: ";
	      status += path;
	      status += " CAUSE: ";
	      status += dlerror();
	      //std::cerr << status << "\n";
	      my_methods[i]->set_status(status);
	    }
	  else
	    {
	      if(my_methods[i]->load())
		{
		  status = "ERR: Cannot Load library: ";
		  status += path;
		  status += " CAUSE: Bad plugin format, not following standards";
		}
	      else
		my_methods[i]->refresh_info();
	    }
	  my_methods[i]->set_status(status);
	  i++;
	}
      num_methods = i;
    }
}

int methodsManager::useMethod(cell **& myCells, int & sollution, std::string & status)
{
  int isIt = 0;
  resolvMethod* myMethod = NULL;
  if(viActualMethod != vMethodsInSystem.end())
    {
      isIt=1;
      // load the symbols
      create_pluginInstance = (create_t*) dlsym(*viActualMethod, "create");
      const char* dlsym_error = dlerror();
      if (dlsym_error) {
	std::cerr << "ERR: Cannot load symbol create: " << dlsym_error << '\n';
        isIt= 0;
      }
    
      destroy_pluginInstance = (destroy_t*) dlsym(*viActualMethod, "destroy");
      dlsym_error = dlerror();
      if (dlsym_error) {
	std::cerr << "ERR: Cannot load symbol destroy: " << dlsym_error << '\n';
        isIt= 0;
      }
      if(isIt)
	{
	  myMethod = create_pluginInstance();
	  if(!myMethod->analyze(myCells))
	    {
	      sollution += myMethod->hasSollution(myCells);
	      status = "using method:  ";
	      status +=  myMethod->retMethodName();
	      status += " got sollution?...";
	      if(sollution)
		status += "yes";
	      else
		status += "no";
	    }
	  else
	    {
	      status = "ERR: method  ";
	      status +=  myMethod->retMethodName();
	      status += " couldn't be used, reason?";	      
	    }
	  destroy_pluginInstance(myMethod);
	  myMethod = NULL;
	}
      ++viActualMethod;
    }
  else
    {
      viActualMethod = vMethodsInSystem.begin();
      isIt=0;
    }

  return isIt;

}

std::vector<struct method_info> methodsManager::ret_plugins_information()
{
  std::vector<struct method_info> information;
  for(int i=0; i <num_methods; i++)
    {
      information.push_back({my_methods[i]->ret_name(),my_methods[i]->ret_description(), my_methods[i]->ret_is_loaded(), my_methods[i]->ret_status()});
    }

  return information;

}

resolvMethod* methodsManager::createMethod()
{
  return create_pluginInstance();
}

void methodsManager::destroyMethod(resolvMethod* myPlugin)
{
  if (myPlugin)
    destroy_pluginInstance(myPlugin);
}

