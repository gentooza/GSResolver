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

CXXFLAGS=-std=c++11
squareMethod.so:squareMethod.cpp  ../../cell.cpp ../../cell.h ../base_method.h
	$(CXX) $(CXXFLAGS) -shared -fPIC -o squareMethod.so squareMethod.cpp ../../cell.cpp

clean:
	rm -f squareMethod.so

.PHONY: clean
