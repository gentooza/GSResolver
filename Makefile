#Copyright 2018 Joaquín Cuéllar
#
#This file is part of GSResolver.
#
#GSResolver is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#GSResolver is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with GSResolver.  If not, see <https://www.gnu.org/licenses/>.

CXXFLAGS=-std=c++11 -Wall
GSResolver:main.cpp tools.cpp resolver.cpp gui.cpp cell.cpp methodsManager.cpp resolver.h gui.h cell.h methodsManager.h ./methods/base_method.h
	$(CXX) $(CXXFLAGS) -o GSResolver main.cpp tools.cpp resolver.cpp gui.cpp cell.cpp methodsManager.cpp -ldl -lncurses

clean:
	rm -f GSResolver

.PHONY: clean

