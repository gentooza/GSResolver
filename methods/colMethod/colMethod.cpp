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


class colMethod : public base_method
{
public:
  int analyze(cell**& myCells) 
  {
    std::vector<int> definedNums;
    std::vector<int>::iterator iterDefinedNums;
    for(int col = 1 ; col <= 9 ; col++)
      {        
	for(int i = 0; i < sudoku_size ; i++)
	  {	  
	    if(myCells[i]->col() == col) //col
	      if(myCells[i]->ret_value())
		definedNums.push_back(myCells[i]->ret_value());
	  }
	for(int j = 0; j < sudoku_size ; j++)
	  {
	    if(myCells[i]->col() == col) //col
	      if(!myCells[j]->ret_value())
		myCells[j]->removeFrmCouldBe(definedNums);
	  }
	definedNums.clear();
      }
    return 0;
  };
  std::string ret_name()
  {
    return "Simple column analisys method";
  };
  std::string ret_description()
  {
    return "We remove as possible the values already defined in other fields in same column";
  }; 

};

// the class factories

extern "C" base_method* create() {
    return new colMethod;
}

extern "C" void destroy(base_method* p) {
    delete p;
}
