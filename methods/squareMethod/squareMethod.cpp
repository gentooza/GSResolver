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

class squareMethod : public base_method
{
public:
  virtual int analyze(cell**& cells)
  {
    //square 1
    //cols 1,2,3
    //rows 1,2,3
    //square 2
    //cols 4,6,7
    //rows 1,2,3
    //etc...
    int col_min = 0, col_max = 0, row_min = 0,row_max = 0;
    std::vector<int> definedNums;
    std::vector<int>::iterator iterDefinedNums;
    std::vector <int> coordinates;
    for(int square = 1 ; square <= 9 ; square++)
      {
	switch(square)
	  {
	  case(1):
	    col_min = row_min = 1;
	    col_max = row_max = 3;
	    break;
	  case(2):
	    col_min = 4;
	    col_max = 6;
	    break;
	  case(3):
	    col_min = 7;
	    col_max = 9;
	  
	    break;
	  case(4):
	    col_min = 1;
	    col_max = 3;
	    row_min = 4;
	    row_max = 6;
	    break;
	  case(5):
	    col_min = 4;
	    col_max = 6;
	    break;
	  case(6):
	    col_min = 7;
	    col_max = 9;	  
	    break;
	  case(7):
	    col_min = 1;
	    col_max = 3;
	    row_min = 7;
	    row_max = 9;
	    break;
	  case(8):
	    col_min = 4;
	    col_max = 6;
	    break;
	  case(9):
	    col_min = 7;
	    col_max = 9;
	    break;
	  default:
	    col_min = col_max = row_min = row_max = 1;
	    break;
	  }
      
      for(int i = 0; i < sudoku_size ; i++)
	{	  
	  coordinates = cells[i]->retPos();
	  if(coordinates.at(0) >= col_min && coordinates.at(0) <= col_max) //col
	    if(coordinates.at(1) >= row_min && coordinates.at(1) <= row_max) //row
	      if(cells[i]->retDefined())
		definedNums.push_back(cells[i]->ret_value());
	}
      for(int i = 0; i < sudoku_size ; i++)
	{
	  coordinates = cells[i]->retPos();
	  if(coordinates.at(0) >= col_min && coordinates.at(0) <= col_max) //col
	    if(coordinates.at(1) >= row_min && coordinates.at(1) <= row_max) //row
	      if(!cells[i]->retDefined())
		  cells[i]->removeFrmCouldBe(definedNums);
	}
      definedNums.clear();
      coordinates.clear();
    }
  return 0;
  };
  std::string ret_name()
  {
    return "Simple squared section analisys method";
  };
  std::string ret_description()
  {
    return "We remove as possible the values already defined in other fields in same squared section";
  }; 
};

// the class factories

extern "C" base_method* create() {
    return new squareMethod;
}

extern "C" void destroy(base_method* p) {
    delete p;
}
