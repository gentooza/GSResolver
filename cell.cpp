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

#include "cell.h"


cell::cell(int num)
{
  if(iValue > 0 && iValue < 10)
    {
      iValue = num;
      defined = 1;
      couldBe.clear();
    }
  else
    {
      iValue = 0;
      defined = 0;
      
      for(int i = 1; i <10 ; i++)
	if(i!=iValue)
	  couldBe.push_back(i);
    }

  iCol = iRow = 0;
  return;
}

cell::cell()
{
  iValue = 0;
  defined = 0;

  for(int i = 1; i <10 ; i++)
    if(i!=iValue)
      couldBe.push_back(i);
 
  return;
}

int cell::set_value(int value)
{
  int failed = 1;
  if(value > 0  && value < 10)
    {
      iValue = value;
      defined = 1;
      
      couldBe.clear();
      /*
      for(int i = 1; i <10 ; i++)
	if(i!=iValue)
	  couldBe.push_back(i);
      */
      failed = 0;
    }
  return failed;
}
void cell::set_position(int col, int row)
{
  //TODO constants here
  if((row > 0 && row <= 9) && (col > 0 && col <= 9))
    {
      iRow = row;
      iCol = col;
    }
}
std::vector<int> cell::retPos()
{
  std::vector<int> coordinates;

  coordinates.push_back(iCol);
  coordinates.push_back(iRow);

  return coordinates;
}

int cell::removeFrmCouldBe(std::vector <int> vectorToRemove)
{
  std::vector <int>::iterator toRemoveIterator;

  for(toRemoveIterator = vectorToRemove.begin(); toRemoveIterator != vectorToRemove.end(); ++toRemoveIterator)
    couldBe.erase(std::remove(couldBe.begin(), couldBe.end(), *toRemoveIterator), couldBe.end());

  return 0;
}

int cell::hasSollution()
{
  int sollution = 0;
  if(!defined)
    {
      if(couldBe.size() == 1)
	sollution = 1;
    }

  return sollution;
}

int cell::solve()
{
  int solved = 0;
  if(!defined)
    {
      if(couldBe.size() == 1)
	{
	  set_value(couldBe.at(0));
	  solved = 1;
	}
    }

  return solved;
}

std::string cell::retPrettyStatus()
{
  std::string status;
  std::vector<int>::iterator alternatives;

  if(iValue && defined)
    status = std::to_string(iValue);
  else
    {
      status = "(";
      for(alternatives = couldBe.begin(); alternatives != couldBe.end(); ++alternatives)
	{
	  status += std::to_string(*alternatives);
	  status += ",";
	}
      status = status.substr(0, status.size()-1);
      status += ")";
    }

  return status;
}
