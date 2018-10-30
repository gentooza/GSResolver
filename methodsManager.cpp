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

void method::load()
{
  if(my_so)
    {
      int is_loaded=1;
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
    }
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
      name = "N/A";
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
	folders.push_back(entry->d_name);
      entry = readdir(dir);
    }

  closedir(dir);

  return;
}
void methodsManager::freePlugins()
{
  std::vector <void*>::reverse_iterator iter;

  if(vMethodsInSystem.size())
    {
      for(iter =  vMethodsInSystem.rbegin(); iter != vMethodsInSystem.rend(); ++iter)
	{
	  if(*iter)
	    dlclose(*iter);
	}
    }
  vMethodsInSystem.clear();
  return;
}

void methodsManager::loadPlugins()
{
  std::vector <std::string> pluginList;
  std::vector <std::string>::iterator iter; 

  freePlugins();
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
	  
	  if (!my_methods[i]->my_so)
	    {
	      std::cerr << "ERR: Cannot load library: " << path << " error: " << dlerror() << '\n';
	    }
	  else
	    {
	      my_methods[i]->load();
	      std::cout << "INFO: plugin loaded " << path << std::endl;
	    }
	}
    }
  dlerror();
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

resolvMethod* methodsManager::createMethod()
{
  return create_pluginInstance();
}

void methodsManager::destroyMethod(resolvMethod* myPlugin)
{
  if (myPlugin)
    destroy_pluginInstance(myPlugin);
}
