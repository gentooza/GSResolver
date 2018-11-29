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

#include "defines.h"
#include "cell.h"
#include "methods_manager.h"


#ifndef _RESOLVER_
#define _RESOLVER_

struct stcell_coordinates
{
  int x;
  int y;
};
struct stcell_position
{
  int col;
  int row;
};

/*!FACADE class, managing the cell map and plugins and merging the external interface of them*/
class resolver
{
 public:
  resolver();
  ~resolver();

  //solving
  int resolve_round();
 
  //methods
  void load_methods();
  int num_methods(){int methods; (inst_methods_manager?methods=inst_methods_manager->num_methods():methods=-1); return methods;};
  std::string method_name(int index);
  std::string method_status(int index);
  std::string method_description(int index);

  
  //cells
  stcell_coordinates cell_coordinates(int index);
  void set_cell_coordinates(int index,int x, int y);
  stcell_position cell_position(int index);
  void set_cell_position(int index,int col, int row);
  int cell_value(int index);
  void set_cell_value(int index,int value);

  int value_possible_in_col(int selected_cell,int value);
  int value_possible_in_row(int selected_cell,int value);
  int value_possible_in_section(int selected_cell,int value);
  int value_possible(int selected_cell,int value);

 private:
  int inum_cells;
  cell ** inst_cells;
  int iRound;
  std::vector <std::string> vStatus;
  int hasSollution;
  methods_manager* inst_methods_manager;
  
};

#endif
