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
  int action_to_do;
  resolver* ourResolver = new resolver();
  gui* our_gui = new gui(sVersion);
  cell ** cells_map = new cell*[81];
  for(int i=0;i<81;i++)
    cells_map[i] = new cell(0);

  our_gui->initGui(cells_map);  
  our_gui->showInfo();
  our_gui->showGui(cells_map);

  while(our_gui->isNotFinished())
    {
      action_to_do = our_gui->eval_keyboard_input(cells_map);
      //If we are loading plugin management screen, load our plugin managment system information
      if(action_to_do == GUI_PLUGIN_MANAGEMENT) 
	{

	}
      our_gui->showGui(cells_map);
    }
  
  delete our_gui;
  delete ourResolver;
  for (int i=80 ; i>=0; i--)
    delete cells_map[i];
  delete cells_map;

  return 0;
}

  
