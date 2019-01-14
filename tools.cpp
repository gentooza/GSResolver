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

std::string getCurrentDate()
{
  std::string myDate;
  std::string myTime;
  time_t t = time(NULL);
  tm* timePtr = localtime(&t);

  myDate = std::to_string(timePtr->tm_year+1900);
  myDate += '-';

  if(timePtr->tm_mon+1 <10)
      myDate += '0';
  myDate += std::to_string(timePtr->tm_mon+1);
  
  myDate += '-';

  if(timePtr->tm_mday <10)
      myDate += '0';
  myDate += std::to_string(timePtr->tm_mday);

  if(timePtr->tm_hour < 10)
      myTime += '0';
  myTime += std::to_string(timePtr->tm_hour);
  
  myTime += ':';
  
  if(timePtr->tm_min < 10)
      myTime += '0';
  myTime += std::to_string(timePtr->tm_min);

  myTime += ':';
  
  if(timePtr->tm_sec < 10)
      myTime += '0';

  if(timePtr->tm_sec > 59)
      myTime += "59";
  else
      myTime += std::to_string(timePtr->tm_sec);

  std::string myWhole = myDate + " " + myTime;
  
  return myWhole;
}

int log_txt(std::string message)
{
  //TODO, hardcoded
  std::string path = "./logs";
  //std::string security_check = "mkdir " + path + " > /dev/null";
  int ret = 0;
  std::string file_name = path + "/" +  getCurrentDate().substr(0,10) + ".log";  
  std::ofstream my_file;

  mkdir(path.c_str(),0755);

  my_file.open(file_name,std::ios::app);

  if(my_file.is_open())
   {
      my_file << getCurrentDate().substr(11) << " > " << message << "\n";
      ret = 0;
    }
  else
    ret = 1;

  my_file.close();

  return ret;
}
