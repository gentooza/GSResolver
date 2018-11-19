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
#include "cell.h"
#include "defines.h"
#include <cstring>


#ifndef _TOOLS_
#define _TOOLS_

int tools_value_possible_in_col(cell **& cells_map,int selected_cell,int value);
int tools_value_possible_in_row(cell **& cells_map,int selected_cell,int value);
int tools_value_possible_in_section(cell **& cells_map,int selected_cell,int value);
int tools_value_possible(cell **& cells_map,int selected_cell,int value);


//TEXT TOOLS
std::vector<std::string> ret_paragraph_with_lines_return(std::string original,unsigned int line_width);

#endif
