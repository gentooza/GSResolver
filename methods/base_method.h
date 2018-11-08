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


class base_method
{
 public:
 base_method(){};
  
  virtual int analyze(cell**&){return 0;};
  int has_sollution(cell **& cells)
  {
    int sollution = 0;
    for(int i = 0; i < sudoku_size ; i++)    
      if(!cells[i]->retDefined())
	sollution += cells[i]->hasSollution();

    return sollution;
  }

  virtual std::string ret_name(){return "N/A";};
  virtual std::string ret_description(){return "N/A";}; 
  
  
};

// the types of the class factories
typedef base_method* create_t();
typedef void destroy_t(base_method*);

#endif
