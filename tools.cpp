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

#include "tools.h"

std::vector<std::string> ret_paragraph_with_lines_return(std::string original,unsigned int line_width, int max_lines)
{
  std::vector<std::string> my_paragraph;
  std::string tmp;
  std::size_t new_pos;
  int current_line=0;

  tmp = original;
  while((tmp.length() > line_width) && (current_line < max_lines))
    {
      new_pos = tmp.substr(0,line_width).find_last_of(" ");
      my_paragraph.push_back(tmp.substr(0,new_pos));
      tmp = tmp.substr(new_pos+1);
      current_line++;
    }
  my_paragraph.push_back(tmp);
  return my_paragraph;
}
