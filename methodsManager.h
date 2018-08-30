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

#include"./methods/resolvMethod.h"

class methodsManager
{
 public:
  methodsManager(){};
  ~methodsManager(){};

  void loadPlugins();
  int useMethod(cell **& myCells, int & sollution, std::string & status);
  resolvMethod* createMethod();
  void destroyMethod(resolvMethod*);

 protected:
  void searchFolders(std::vector <std::string> &);
  void freePlugins();
 private:
  std::vector <void*> vMethodsInSystem;
  std::vector <void*>::iterator viActualMethod;
  create_t* create_pluginInstance;
  destroy_t* destroy_pluginInstance;
};

#endif
