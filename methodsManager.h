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

#ifndef _METHODS_MANAGER_
#define _METHODS_MANAGER_

#include <dlfcn.h>
#include <vector>
#include <dirent.h>
#include <iterator>
#include <string.h>

#include"./methods/base_method.h"

class method
{
 public:
  method(){my_so = NULL; is_loaded=0; priority = -1;};
  ~method();

  void set_name(std::string new_name){name = new_name;};
  void set_path(std::string path){full_path = path;};
  void set_status(std::string new_status){status = new_status;};
  
  void *my_so;
  int load();
  void refresh_info();

  std::string ret_name(){return name;};
  std::string ret_description(){return description;};
  std::string ret_status(){return status;};
  int ret_is_loaded(){return is_loaded;};
    
 private:
  std::string name;
  std::string description;
  std::string full_path;
  std::string status;
  int is_loaded;
  int priority;
  create_t* create_plugin_instance;
  destroy_t* destroy_plugin_instance;
};



class methodsManager
{
 public:
  methodsManager(){num_methods = 0;};
  ~methodsManager(){};

  void load_plugins();
  void free_plugins();
  int useMethod(cell **& myCells, int & sollution, std::string & status);
  base_method* createMethod();
  void destroyMethod(base_method*);

  std::vector<struct method_info> ret_plugins_information();

 protected:
  void search_plugins_folders(std::vector <std::string> &);

 private:
  method** my_methods;
  int num_methods;
  std::vector <void*> vMethodsInSystem;
  std::vector <void*>::iterator viActualMethod;
  create_t* create_pluginInstance;
  destroy_t* destroy_pluginInstance;
};

#endif
