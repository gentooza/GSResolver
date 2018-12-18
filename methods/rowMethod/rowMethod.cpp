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

#include "../base_method.h"


class rowMethod : public base_method
{
public:
  virtual int analyze(cell**& cells)
  {
    std::vector<int> definedNums;
    std::vector<int>::iterator iterDefinedNums;
    for(int row = 1 ; row <= 9 ; row++)
      {        
	for(int i = 0; i < sudoku_size ; i++)
	  {	
	    if(cells[i]->row() == row) //row
	      if(cells[i]->retDefined())
		definedNums.push_back(cells[i]->ret_value());
	  }
	for(int i = 0; i < sudoku_size ; i++)
	  {	  
	    if(cells[i]->row() == row) //row
	      if(!cells[i]->retDefined())
		cells[i]->removeFrmCouldBe(definedNums);
	  }
	definedNums.clear();
      }
    return 0;
  };
  std::string ret_name()
  {
    return "Simple rows analisys method";
  };
  std::string ret_description()
  {
    return "We remove as possible the values already defined in other fields in same row";
  }; 
};

// the class factories

extern "C" base_method* create() {
  return new rowMethod;
}

extern "C" void destroy(base_method* p) {
  delete p;
}
