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


class rowCouplesMethod : public base_method
{
public:


  int couple_already_possible(std::vector <int> new_couple, std::vector < std::vector <int>> couples_group)
  {
    int it_is = 0;
    std::vector <std::vector <int>>::iterator iter;

    for(iter = couples_group.begin(); iter != couples_group.end(); ++iter)
      {
	if(iter->size() == 2 && new_couple.size() == 2)
	  {
	    if((*iter)[0] == new_couple[0] && (*iter)[1] == new_couple[1])
	      it_is = 1;
	    else if((*iter)[1] == new_couple[0] && (*iter)[0] == new_couple[1])
	      it_is = 1;
	  }
      }
  }
  
  virtual int analyze(cell**& cells)
  {
    //square 1
    //cols 1,2,3
    //rows 1,2,3
    //square 2
    //cols 4,5,6
    //rows 1,2,3
    //etc...
    int col_min = 0, col_max = 0, row_min = 0,row_max = 0;
    std::vector< std::vector <int>> possibleCouples;
    std::vector< std::vector <int>> definedCouples;
    std::vector< std::vector <int>>::iterator iterDefinedCouples;
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
		if(!cells[i]->ret_value())
		  {
		    if(cells[i]->retCouldBe().size() == 2) //couple possible here
		      {
			if(couple_already_possible(cells[i]->retCouldBe(),possibleCouples))
			  {
			    if(!couple_already_possible(cells[i]->retCouldBe(),definedCouples))
			      definedCouples.push_back(cells[i]->retCouldBe());
			  }
			else
			  {
			    if(!couple_already_possible(cells[i]->retCouldBe(),definedCouples))
			      possibleCouples.push_back(cells[i]->retCouldBe());
			  }
		      }
		  }
	  }
	if(definedCouples.size())
	  {
	    for(int i = 0; i < sudoku_size ; i++)
	      {
		coordinates = cells[i]->retPos();
		if(coordinates.at(0) >= col_min && coordinates.at(0) <= col_max) //col
		  if(coordinates.at(1) >= row_min && coordinates.at(1) <= row_max) //row
		    if(!cells[i]->ret_value())
		      {
			if(cells[i]->retCouldBe().size() != 2)
			  {
			    for(iterDefinedCouples = definedCouples.begin(); iterDefinedCouples != definedCouples.end(); ++iterDefinedCouples)
			      {
				cells[i]->removeFrmCouldBe(*iterDefinedCouples);
			      }
			  }
		      }
	      }
	  }
	possibleCouples.clear();
	definedCouples.clear();
	coordinates.clear();
      }
    return 0;
  };
  std::string ret_name()
  {
    return "Simple rows-couples analisys method";
  };
  std::string ret_description()
  {
    return "We remove as possible the couples already defined in other fields in same row";
  }; 
};

// the class factories

extern "C" base_method* create() {
  return new rowCouplesMethod;
}

extern "C" void destroy(base_method* p) {
  delete p;
}
