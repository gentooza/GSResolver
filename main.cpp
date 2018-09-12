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
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>


#include "resolver.h"
#include "gui.h"


int main()
{
  std::string sVersion = "0.1"; 
  std::vector< std::vector<std::string> > newValues;
  std::vector< std::vector<int> > values;
  std::vector <std::string> status;
  int programOption;
  char option;
  resolver* ourResolver = new resolver();
  gui* ourGui = new gui(sVersion);
  cell ** myCells = new cell*[81];
  for(int i=0;i<81;i++)
    myCells[i] = new cell(0);

  ourGui->initGui(myCells);
  
  ourGui->showInfo();

  ourGui->showGui();

  while(ourGui->isNotFinished())
    {
      ourGui->eval_input();
      ourGui->showGui();
    }
  
  //implementing ncurses
  delete ourGui;
  return 0;
  //
  values = ourGui->askForValues();
  
  ourResolver->setValues(values);

  ourResolver->loadMethods();

  values.clear();

  myCells = ourResolver->getCurrentCells();
  ourResolver->getCurrentStatus(status);
  ourGui->clear();
  ourGui->showCurrent(myCells,status);
  ourGui->showOptions();
  /* Key reading loop */
  while (1)
    {
      
      programOption = ourGui->getOption();            
      if (programOption == OPT_RESOLVE) //resolve round
	{
	  if(ourResolver->analyze())
	    ourResolver->resolveOne();
	    	  
	  myCells = ourResolver->getCurrentCells();
	  ourResolver->getCurrentStatus(status);
	  ourGui->showCurrent(myCells,status);
	  ourResolver->clearStatus();
	  ourGui->showOptions();
	}
      else if (programOption == OPT_RESOLVE_ALL) //resolve all
	{
	  while(ourResolver->analyze())
	    {
	      myCells = ourResolver->getCurrentCells();
	      ourResolver->getCurrentStatus(status);
	      ourGui->showCurrent(myCells,status);
	      ourResolver->resolveOne();
	      newValues.clear();
	    }
	  newValues = ourResolver->getCurrent();
	  ourResolver->getCurrentStatus(status);
	  ourGui->showCurrent(newValues,status);
	  ourGui->showOptions();
	}
      else if(programOption == OPT_VERSION)
	{
	  newValues = ourResolver->getCurrent();
	  ourResolver->getCurrentStatus(status);
	  ourGui->showCurrent(newValues,status);
	  ourGui->showInfo();
	  ourGui->showOptions();
	}
      else if (programOption == OPT_QUIT)
	{
	  delete ourResolver;
	  delete ourGui;
	  return 0;  /* Press 'Q' to quit program */
	}
    }  

  delete ourResolver;
  delete ourGui;
  
  return 0;
}

  
