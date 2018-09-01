Gentooza's Sudokus Resolver
===
#1- Description
GSResolver can resolve sudokus for you, it's a terminal program only tested under GNU/Linux (ubuntu 16.04 amd64) and has been designed to program by patterns and by plugins.
For the instance no patterns present (at least not actively, perhaps some factory pattern is already there?), but I'will remade the application to achieve that. What it' s already working is a basic plugin system to easily add any algorithm you can imagine intended to solve a sudoku.

#2- Plugins development
You have to create a folder inside methods with the same name as your .so library. Please take resolvMethod.h and any of the already made algorithms as examples. (Makefiles, .cpp, etc.)

cell.h and cell.cpp can already give you an idea of the fields map we pass as parameter to an algorithm

#3- Dependencies
GSResolver is intended to be used with minimal dependencies in any actual GNU/Linux system.
It depends on:
+ NCurses (under the X11 license)
+ GlibC 

#4- Please enjoy
It's only for having fun and learn!

#5- Copyright
Copyright (C) 2018 Joaquín Cuéllar

#6- License
```
Gentooza's Sudokus Resolver is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Gentooza's Sudokus Resolver is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
```

