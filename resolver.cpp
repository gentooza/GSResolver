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
  vstatus.clear();
  iround = 0;
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

/*!sudoku solving*/
int resolver::resolve_round()
{
  int has_sollution = 0;
  std::string message = "Round:" + std::to_string(iround) + " gonna try:" + std::to_string(num_methods()) + " methods";
  vstatus.push_back(message);
  for(int i=0; i < num_methods(); i++)
    {
      vstatus.push_back(inst_methods_manager->resolve(i,inst_cells));
      
    }
  iround++;
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
  stcell_coordinates new_coordinates {-1,-1};
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
  stcell_position new_position {-1,-1};
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
void resolver::set_cell_value(int index,int value)
{
  if(inst_cells && index < inum_cells && index >= 0)
    if(value>=0 && value <=9)
      value = inst_cells[index]->set_value(value);

  return;
}
/*!has cell a sollution?*/
int resolver::cell_has_sollution(int index)
{
  int ret = 0;
  if(inst_cells && index < inum_cells && index >= 0)
    ret = inst_cells[index]->hasSollution();
  return ret;
}
/*!solve this cell*/
int resolver::cell_solve(int index)
{
  int ret = 0;
  if(inst_cells && index < inum_cells && index >= 0)
    ret = inst_cells[index]->solve();
  return ret; 
}

int resolver::value_possible_in_col(int selected_cell,int value)
{
  int ret = 1;
  int i = selected_cell -9;
  while (i >=0)
    {
      if(inst_cells[i]->ret_value() == value)
	ret = 0;
      i = i -9;
    }

  i = selected_cell +9;
  while (i < SUDOKU_SIZE)
    {
      if(inst_cells[i]->ret_value() == value)
	ret = 0;
      i = i +9;
    }

  return ret;
}

int resolver::value_possible_in_row(int selected_cell,int value)
{
  int ret = 1;
  int* cells_in_section = NULL;
  //in row 1
  if(selected_cell>=0 && selected_cell <=8)
    cells_in_section = new int[9]{0,1,2,3,4,5,6,7,8};
  //in row 2
  else if(selected_cell>=9 && selected_cell <=17)
    cells_in_section = new int[9]{9,10,11,12,13,14,15,16,17};
  //in row 3
  else if(selected_cell>=18 && selected_cell <=26)
    cells_in_section = new int[9]{18,19,20,21,22,23,24,25,26};
  //in row 4
  else if(selected_cell>=27 && selected_cell <=35)
    cells_in_section = new int[9]{27,28,29,30,31,32,33,34,35};
  //in row 5
  else if(selected_cell>=36 && selected_cell <=44)
    cells_in_section = new int[9]{36,37,38,39,40,41,42,43,44};
  //in row 6
  else if(selected_cell>=45 && selected_cell <=53)
    cells_in_section = new int[9]{45,46,47,48,49,50,51,52,53};
  //in row 7
  else if(selected_cell>=54 && selected_cell <=62)
    cells_in_section = new int[9]{54,55,56,57,58,59,60,61,62};
  //in row 8
  else if(selected_cell>=63 && selected_cell <=71)
    cells_in_section = new int[9]{63,64,65,66,67,68,69,70,71};
  //in row 9
  else if(selected_cell>=72 && selected_cell <=80)
    cells_in_section = new int[9]{72,73,74,75,76,77,78,79,80};
  else
    cells_in_section = new int[9]{selected_cell,selected_cell,selected_cell,selected_cell,selected_cell,selected_cell,selected_cell,selected_cell,selected_cell};

  for(int i=0; i<9; i++)
    {
      if(selected_cell != cells_in_section[i])
	{
	  //check if value is already set in any section cell
	  if(value == inst_cells[cells_in_section[i]]->ret_value())
	    ret = 0;
	}
    }
  return ret;

}


int resolver::value_possible_in_section(int selected_cell,int value)
{
  int ret = 1;
  int* cells_in_section = NULL;
  //in section 1
  if((selected_cell>=0 && selected_cell <=2) || (selected_cell>=9 && selected_cell <=11) || (selected_cell>=18 && selected_cell <=20))
    cells_in_section = new int[9]{0,1,2,9,10,11,18,19,20};
  //in section 2
  else if((selected_cell>=3 && selected_cell <=5) ||
	  (selected_cell>=12 && selected_cell <=14) || (selected_cell>=21 && selected_cell <=23))
    cells_in_section = new int[9]{3,4,5,12,13,14,21,22,23};
  //in section 3
  else if((selected_cell>=6 && selected_cell <=8) ||
	  (selected_cell>=15 && selected_cell <=17) || (selected_cell>=24 && selected_cell <=26))
    cells_in_section = new int[9]{6,7,8,15,16,17,24,25,26};
  //in section 4
  else if((selected_cell>=27 && selected_cell <=29) ||
	  (selected_cell>=36 && selected_cell <=38) || (selected_cell>=45 && selected_cell <=47))
    cells_in_section = new int[9]{27,28,29,36,37,38,45,46,47};
  //in section 5
  else if((selected_cell>=30 && selected_cell <=32) ||
	  (selected_cell>=39 && selected_cell <=41) || (selected_cell>=48 && selected_cell <=50))
    cells_in_section = new int[9]{30,31,32,39,40,41,48,49,50};
  //in section 6
  else if((selected_cell>=33 && selected_cell <=35) ||
	  (selected_cell>=42 && selected_cell <=44) || (selected_cell>=51 && selected_cell <=53))
    cells_in_section = new int[9]{33,34,35,42,43,44,51,52,53};
  //in section 7
  else if((selected_cell>=54 && selected_cell <=56) ||
	  (selected_cell>=63 && selected_cell <=65) || (selected_cell>=72 && selected_cell <=74))
    cells_in_section = new int[9]{54,55,56,63,64,65,72,73,74};
  //in section 8
  else if((selected_cell>=57 && selected_cell <=59) ||
	  (selected_cell>=66 && selected_cell <=68) || (selected_cell>=75 && selected_cell <=77))
    cells_in_section = new int[9]{57,58,59,66,67,68,75,76,77};
  //in section 9
  else if((selected_cell>=60 && selected_cell <=62) ||
	  (selected_cell>=69 && selected_cell <=71) || (selected_cell>=78 && selected_cell <=80))
    cells_in_section = new int[9]{60,61,62,69,70,71,78,79,80};
  else
    cells_in_section = new int[9]{selected_cell,selected_cell,selected_cell,selected_cell,selected_cell,selected_cell,selected_cell,selected_cell,selected_cell};

  for(int i=0; i<9; i++)
    {
      if(selected_cell != cells_in_section[i])
	{
	  //check if value is already set in any section cell
	  if(value == inst_cells[cells_in_section[i]]->ret_value())
	    ret = 0;
	}
    }
  return ret;
}

int resolver::value_possible(int selected_cell,int value)
{
  int ret = 0;
  //values are logic?
  if (selected_cell >=0 && selected_cell < SUDOKU_SIZE)
    {
      if(value >=1 && value <=9)
	{
	  //is value in section?
	  if(value_possible_in_section(selected_cell,value))
	    {
	      if(value_possible_in_row(selected_cell,value))
		{
		  if(value_possible_in_col(selected_cell,value))
		    {
		      ret = 1;
		    }
		  else
		    {
		      ret = -3;
		    }
		}
	      else
		{
		  ret = -2;
		}	      
	    }
	  else
	    {
	      ret = -1;
	    }
 
	}
    }
  return ret;
}
