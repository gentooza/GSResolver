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
  inst_cells =  new cell* [sudoku_size];
  inum_cells = sudoku_size;
  for (int i=0; i < sudoku_size; i++)
    inst_cells[i] = new cell();
  vStatus.clear();
  iRound = 0;
  vStatus.push_back("Round 0, original and possible values only");
  inst_methods_manager = new methods_manager();
  return;
}
resolver::~resolver()
{
  for(int i = sudoku_size-1 ; i >= 0 ; i--)
    if(inst_cells[i])
      delete inst_cells[i];
  delete inst_cells;
  delete inst_methods_manager;
  return;
}

/*!methods related functions*/
void resolver::load_methods()
{
  inst_methods_manager->free_plugins();
  inst_methods_manager->load_plugins(); 
  return;
}

std::string resolver::method_name(int index)
{
  std::string tmp = "**empty**";
  if(inst_methods_manager)
    tmp = inst_methods_manager->method_name(index);

  return tmp;
}
std::string resolver::method_status(int index)
{
  std::string tmp = "**empty**";
  if(inst_methods_manager)
    tmp = inst_methods_manager->method_status(index);

  return tmp;
}
std::string resolver::method_description(int index)
{
  std::string tmp = "**empty**";
  if(inst_methods_manager)
    tmp = inst_methods_manager->method_description(index);

  return tmp;
}

/*!cells related functions*/

stcell_coordinates resolver::cell_coordinates(int index)
{
  stcell_coordinates = new_coordinates {-1,-1};
  if(inst_cells && index < inum_cells && index >= 0)
    {
      new_coordinates.x = inst_cells[index]->x();
      new_coordinates.y = inst_cells[index]->y();
    }

  return new_coordinates;
}

void resolver::set_cell_coordinates(int index, int x, int y)
{
  if(inst_cells && index < inum_cells && index >= 0)
      inst_cells[index]->set_coordinates(x,y);

  return;
}

stcell_position resolver::cell_position(int index)
{
  stcell_position = new_position {-1,-1};
  if(inst_cells && index < inum_cells && index >= 0)
    {
      new_position.col = inst_cells[index]->col();
      new_position.row = inst_cells[index]->row();
    }

  return new_position;
}

void resolver::set_cell_position(int index, int col, int row)
{
  if(inst_cells && index < inum_cells && index >= 0)
      inst_cells[index]->set_position(col,row);

  return;
}

int resolver::cell_value(int index)
{
  int value = -1;
  if(inst_cells && index < inum_cells && index >= 0)
    value = inst_cells[index]->ret_value();

  return value;
}
