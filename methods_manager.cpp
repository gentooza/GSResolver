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

#include"methods_manager.h"


method::~method()
{
  if(my_so)
    {
      dlclose(my_so);
    }
};

int method::load()
{
  int ret = -1;  

  is_loaded=1;
  // load the symbols
  create_plugin_instance = (create_t*) dlsym(my_so, "create");
  const char* dlsym_error = dlerror();
  if (dlsym_error) {
    std::cerr << "ERR: Cannot load symbol create: " << dlsym_error << '\n';
    is_loaded= 0;
  }
  destroy_plugin_instance = (destroy_t*) dlsym(my_so, "destroy");
  dlsym_error = dlerror();
  if (dlsym_error) {
    std::cerr << "ERR: Cannot load symbol destroy: " << dlsym_error << '\n';
    is_loaded= 0;
  }    
    
  if(is_loaded)
    ret = 0;
  return ret;
}

void method::refresh_info(std::string default_name, std::string default_description )
{
  if(is_loaded)
    {
      base_method* myMethod = create_plugin_instance();
      name = myMethod->ret_name();
      description = myMethod->ret_description();
      destroy_plugin_instance(myMethod);
    }
  else
    {
      name = default_name;
      description = default_description;
    }
}

void methods_manager::search_plugins_folders(std::vector <std::string>  & folders)
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
void methods_manager::free_plugins()
{
  if(inum_methods)
    {
      for(int i=inum_methods-1; i >= 0;i--)
	{
	  delete inst_methods[i];
	}
      delete inst_methods;      
    }
  
  return;
}


void methods_manager::load_plugins()
{
  std::vector <std::string> plugins_list;
  std::vector <std::string>::iterator iter; 

  inum_methods = 0;
  search_plugins_folders(plugins_list);
  if(plugins_list.size())
    {
      inst_methods = new method*[plugins_list.size()];
      int i=0;
      for(iter = plugins_list.begin(); iter != plugins_list.end(); ++iter)
	{
	  std::string path = "./methods/";
	  path += *iter;
	  path += "/";
	  path += *iter;
	  path += ".so";
	  inst_methods[i] = new method();
	  inst_methods[i]->set_path(path);
	  inst_methods[i]->my_so =  dlopen(path.c_str(), RTLD_LAZY);
	  std::string status = "Plugin correctly loaded";	  
	  //loading symbols
	  if (!inst_methods[i]->my_so) //ERROR
	    {
	      std::string error = dlerror();
	      status = "ERR: Cannot open library: ";
	      status += path;
	      status += " CAUSE: ";
	      status += error;
	      //std::cerr << status << "\n";
	      inst_methods[i]->set_status(status);
	      inst_methods[i]->set_error(error);
	    }
	  else	  //loading symbols if NO ERROR
	    {
	      inst_methods[i]->set_error("NO");
	      if(inst_methods[i]->load())
		{
		  status = "ERR: Cannot Load library: ";
		  status += path;
		  status += " CAUSE: Bad plugin format, not following standards";
		  inst_methods[i]->set_error("Bad plugin format, not following standards");
		}	      
	    }
	  inst_methods[i]->refresh_info(*iter,"**nothing**");
	  inst_methods[i]->set_status(status);
	  i++;
	}
      inum_methods = i;
    }
}

base_method* methods_manager::createMethod()
{
  return create_pluginInstance();
}

void methods_manager::destroyMethod(base_method* myPlugin)
{
  if (myPlugin)
    destroy_pluginInstance(myPlugin);
}

std::string methods_manager::method_name(int index)
{
  std::string name = "**empty**";
  if(inst_methods && index < inum_methods && index >= 0)
    name = inst_methods[index]->ret_name();

  return name;
}
std::string methods_manager::method_status(int index)
{
  std::string status = "**empty**";
  if(inst_methods && index < inum_methods && index >= 0)
    name = inst_methods[index]->ret_status();

  return name;
}
std::string methods_manager::method_description(int index)
{
  std::string description = "**empty**";
  if(inst_methods && index < inum_methods && index >= 0)
    name = inst_methods[index]->ret_dscription();

  return name;
}
