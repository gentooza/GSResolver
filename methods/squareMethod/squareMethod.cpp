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

#include "../resolvMethod.h"


class squareMethod : public resolvMethod
{
public:
  virtual int analyze(cell**& cells)
  {

    setMethodName("Simple squared section analisys method");
    setMethodDescription("We remove as possible the values already defined in other fields in same squared section");
  //square 1
  //cols 0,1,2
  //rows 0,1,2
  //square 2
  //cols 3,4,5
  //rows 0,1,2
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
	  col_min = row_min = 0;
	  col_max = row_max = 2;
	  break;
	case(2):
	  col_min = 3;
	  col_max = 5;
	  break;
	case(3):
	  col_min = 6;
	  col_max = 8;
	  
	  break;
	case(4):
	  col_min = 0;
	  col_max = 2;
	  row_min = 3;
	  row_max = 5;
	  break;
	case(5):
	  col_min = 3;
	  col_max = 5;
	  break;
	case(6):
	  col_min = 6;
	  col_max = 8;	  
	  break;
	case(7):
	  col_min = 0;
	  col_max = 2;
	  row_min = 6;
	  row_max = 8;
	  break;
	case(8):
	  col_min = 3;
	  col_max = 5;
	  break;
	case(9):
	  col_min = 6;
	  col_max = 8;
	  break;
	default:
	  col_min = col_max = row_min = row_max = 0;
	  break;
	}
      
      for(int i = 0; i < sudoku_size ; i++)
	{	  
	  coordinates = cells[i]->retPos();
	  if(coordinates.at(0) >= col_min && coordinates.at(0) <= col_max) //col
	    if(coordinates.at(1) >= row_min && coordinates.at(1) <= row_max) //row
	      if(cells[i]->retDefined())
		definedNums.push_back(cells[i]->retValue());
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

};

// the class factories

extern "C" resolvMethod* create() {
    return new squareMethod;
}

extern "C" void destroy(resolvMethod* p) {
    delete p;
}
