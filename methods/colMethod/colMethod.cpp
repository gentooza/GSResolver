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


class colMethod : public resolvMethod
{
public:
  virtual int analyze(cell**& myCells) 
  {

    setMethodName("Simple column analisys method");
    setMethodDescription("We remove as possible the values already defined in other fields in same column");
  
    //square 1
    //cols 0,1,2
    //rows 0,1,2
    //square 2
    //cols 3,4,5
    //rows 0,1,2
    //etc...
    std::vector<int> definedNums;
    std::vector<int>::iterator iterDefinedNums;
    std::vector <int> coordinates;
    for(int col = 0 ; col < 9 ; col++)
      {        
	for(int i = 0; i < sudoku_size ; i++)
	  {	  
	    coordinates = myCells[i]->retPos();	
	    if(coordinates.at(0) == col) //col
	      if(myCells[i]->retDefined())
		definedNums.push_back(myCells[i]->ret_value());
	  }
	for(int i = 0; i < sudoku_size ; i++)
	  {
	    coordinates = myCells[i]->retPos();
	    if(coordinates.at(0) == col) //col
	      if(!myCells[i]->retDefined())
		myCells[i]->removeFrmCouldBe(definedNums);
	  }
	definedNums.clear();
	coordinates.clear();
      }
    return 0;
  };

};

// the class factories

extern "C" resolvMethod* create() {
    return new colMethod;
}

extern "C" void destroy(resolvMethod* p) {
    delete p;
}
