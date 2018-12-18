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


class colCouplesMethod : public base_method
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
    std::vector< std::vector <int>> possibleCouples;
    std::vector< std::vector <int>> definedCouples;
    std::vector< std::vector <int>>::iterator iterDefinedCouples;
    for(int col = 1 ; col <= 9 ; col++)
      {        
	for(int i = 0; i < sudoku_size ; i++)
	  {	  
	    if(cells[i]->col() == col) //col
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
		if(cells[i]->col() == col) //col
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
      }
    return 0;
  };
  std::string ret_name()
  {
    return "Simple cols-couples analisys method";
  };
  std::string ret_description()
  {
    return "We remove as possible the couples already defined in other fields in same column";
  }; 
};

// the class factories

extern "C" base_method* create() {
  return new colCouplesMethod;
}

extern "C" void destroy(base_method* p) {
  delete p;
}
