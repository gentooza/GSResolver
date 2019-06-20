# THIS IS A MIRROR OF THE OFFICIAL REPOSITORY: [http://git.savannah.nongnu.org/cgit/gsresolver.git]

Gentooza's Sudokus Resolver
===========================
## Description

GSResolver can resolve sudokus for you, it's a terminal program only tested under GNU/Linux (ubuntu 16.04 amd64) and has been designed to program by patterns and by plugins.

I tried a FACADE pattern present in resolver class, it works as an interface of methods, method manager and cells, for our GUI.

It's already implemented a basic POSIX plugin system to easily add any algorithm you can imagine intended to solve a sudoku.

## Plugins development

You have to create a folder inside methods with the same name as your .so library. Please take resolvMethod.h and any of the already made algorithms as examples. (Makefiles, .cpp, etc.)

cell.h and cell.cpp can already give you an idea of the fields map we pass as parameter to an algorithm

## Dependencies

GSResolver is intended to be used with minimal dependencies in any actual GNU/Linux system.

It depends on:

+ NCurses (under the X11 license)
+ GlibC

## Please enjoy

It's only for having fun and learn!

## Copyright

Copyright (C) 2018 Joaquín Cuéllar

## License

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

