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

#include <iostream>
#include <vector>
#include <limits>
#include <string>

#include "../cell.h"
#include "../defines.h"

#ifndef _RESOLV_METHOD_
#define _RESOLV_METHOD_


class resolvMethod
{
 public:
 resolvMethod()
   : iStatus(0) {};
  virtual ~resolvMethod(){};

  virtual int analyze(cell**&){return 0;};
  int hasSollution(cell **& cells)
  {
    int sollution = 0;
    for(int i = 0; i < sudoku_size ; i++)    
      if(!cells[i]->retDefined())
	sollution += cells[i]->hasSollution();

    return sollution;
  }
  int retStatus(){return iStatus;};
  int setMethodName(std::string newName){sName = newName;};
  int setMethodDescription(std::string newDescription){sDescription = newDescription;};

  std::string retMethodName(){return sName;};
  std::string retMethodDescription(){return sDescription;}; 
  
  
 protected:
  int iStatus;
  std::string sName;
  std::string sDescription;  
};

// the types of the class factories
typedef resolvMethod* create_t();
typedef void destroy_t(resolvMethod*);

#endif
