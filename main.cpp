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
  std::string sVersion = "0.1 ALPHA"; 
  std::vector< std::vector<std::string> > newValues;
  std::vector< std::vector<int> > values;
  std::vector <std::string> status;
  int action_to_do;
  resolver* our_resolver = new resolver();
  gui* our_gui = new gui(sVersion);
  

  std::vector<struct method_info> methods_information;
  
  our_gui->initGui(our_resolver);  
  our_gui->showInfo();
  our_gui->show_gui(our_resolver);

  while(our_gui->isNotFinished())
    {
      action_to_do = our_gui->eval_keyboard_input(our_resolver);
      //If we are loading plugin management screen, load our plugin managment system information
      if(action_to_do == ACT_ASK_FOR_PLUGINS) 
	{
	  our_resolver->load_methods();
	}
      if(action_to_do == ACT_RESOLVE_ROUND)
	{
	  //TODO
	  //our_resolver->resolve_round();
	}
      our_gui->show_gui(our_resolver);

    }
  
  delete our_gui;
  delete our_resolver;

  return 0;
}

  
