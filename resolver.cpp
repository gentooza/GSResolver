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

#include "resolver.h"


resolver::resolver()
{
  myCells =  new cell* [sudoku_size];
  for (int i=0; i < sudoku_size; i++)
    myCells[i] = new cell();
  vStatus.clear();
  iRound = 0;
  vStatus.push_back("Round 0, original and possible values only");
  myPluginManager = new methodsManager();
  return;
}
resolver::~resolver()
{
  for(int i = sudoku_size-1 ; i >= 0 ; i--)
    if(myCells[i])
      delete myCells[i];
  delete myCells;
  delete myPluginManager;
  return;
}

std::vector<struct method_info> resolver::load_methods()
{
  std::vector<struct method_info> information;
 
  myPluginManager->loadPlugins();
  information = myPluginManager->ret_plugins_information();
  
  return information;
}

int  resolver::setValues(std::vector< std::vector<int> > values) //TODO, its not needed anymore
{
  std::vector< std::vector<int> >::iterator rowIterator;
  std::vector<int>::iterator cellIterator;
  int i = 0;
  int row = 0;
  int col = 0;

  for(rowIterator = values.begin(); rowIterator != values.end(); ++rowIterator)
    {
    for(cellIterator = rowIterator->begin(); cellIterator != rowIterator->end(); ++cellIterator)
      {
	if(i<sudoku_size)
	  {
	    myCells[i]->set_value(*cellIterator);
	  }
	i++;
	col++;
      }
    row++;
    col = 0;
    }
  return 0;
}

int  resolver::analyze()
{
  int sollution = 0;
  //resolvMethod* myMethod = NULL;
  std::string status;

  while(myPluginManager->useMethod(myCells,sollution,status) > 0)
    {      
      vStatus.push_back(status);
    }

  return sollution;
}

std::vector< std::vector<std::string> > resolver::getCurrent()
{
  std::vector< std::vector<std::string> > currentValues;
  std::vector<std::string> currentRow;
  int i = 0;
  int icurrent_row = 0;
  int icurrent_field = 0;

  while(i < sudoku_size)
    {
      if(icurrent_field >= 9)
	{
	  currentValues.push_back(currentRow);
	  currentRow.clear();
	  icurrent_field = 0;
	}
      currentRow.push_back(myCells[i]->retPrettyStatus());
      i++;
      icurrent_field++;
    }
  if(icurrent_field >= 9)
    {
      currentValues.push_back(currentRow);
      currentRow.clear();
      icurrent_field = 0;
    }
      
  return currentValues;
}

int resolver::resolveOne()
{
  int solved = 0;
  int i = 0;
  while(i<sudoku_size && !solved)
    {
      if(myCells[i]->hasSollution())
	if(myCells[i]->solve())
	  solved = 1;
      i++;
    }
  return solved;
}
