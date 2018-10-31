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
#include "methodsManager.h"


#ifndef _RESOLVER_
#define _RESOLVER_

class resolver
{
 public:
  resolver();
  ~resolver();

  std::vector<struct method_info> load_methods();
  
  int setValues(std::vector< std::vector<int> > values);
  int analyze();
  std::vector< std::vector <std::string> > getCurrent();
  cell ** getCurrentCells(){return myCells;};
  
  void getCurrentStatus(std::vector <std::string> & status){status.clear(); status = vStatus;};
  void clearStatus(){vStatus.clear();};
  void newRound(){iRound++;vStatus.clear();std::string message = "Round "; message += std::to_string(iRound); vStatus.push_back(message);};
  int resolveOne();
    

 private:
  cell ** myCells;
  int iRound;
  std::vector <std::string> vStatus;
  int hasSollution;
  methodsManager* myPluginManager;
  
};

#endif
