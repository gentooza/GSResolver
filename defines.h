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

#ifndef _MY_DEFINES_
#define _MY_DEFINES_

const int sudoku_size = 81;
const int SUDOKU_SIZE = 81;
const int COLUMNS = 9;
const int ROWS = 9;

struct method_info
{
  std::string name;
  std::string description;
  int loaded;
  std::string status;
};

#endif
