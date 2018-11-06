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

#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <algorithm>

#include "defines.h"
#ifndef _CELL_
#define _CELL_

int getInt();

class cell
{
 public:
  cell(int num);
  cell();
  ~cell(){return;};

  int set_value(int value);
  int ret_value(){return iValue;};
  int setDefined(int newDefined){defined = newDefined;};
  int retDefined(){return defined;};
  int setCouldBe(std::vector <int> newCouldBe){couldBe = newCouldBe;};
  std::vector <int> retCouldBe(){return couldBe;};
  int hasSollution();
  int solve();
  int removeFrmCouldBe(int number){/*TODO*/ return 0;};
  int removeFrmCouldBe(std::vector <int> vectorToRemove);
  std::string retPrettyStatus();

  int set_position(int col, int row);
  int ret_col(){return iCol;};
  int ret_row(){return iRow;};
  
  int set_coordinates(int x, int y){GUI_coordinate_x=x; GUI_coordinate_y=y;};
  int ret_y(){return GUI_coordinate_y;};
  int ret_x(){return GUI_coordinate_x;};
  
  std::vector<int> retPos();
  
 private:
  int iValue;
  int defined;
  std::vector <int> couldBe;
  int iRow;
  int iCol;
  int GUI_coordinate_x;
  int GUI_coordinate_y;
};

#endif
