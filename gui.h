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
#include <string>
#include <limits>
#include <stdlib.h>
#include <termios.h>
#include <ncurses.h>
#include <time.h>

#include "defines.h"
#include "cell.h"

#ifndef _GUI_
#define _GUI_

#define clearScreen() printf("\033[H\033[J")

enum options
{
  OPT_RESOLVE = 'r',
  OPT_RESOLVE_ALL = 'R',
  OPT_VERSION = 'v',
  OPT_QUIT = 'Q',
  OPT_STEP = 's',
  OPT_CHANGE = 'c',
  OPT_INVALID = 'x'
};

enum gui_status
  {
    GUI_MAIN = 0,
    GUI_SUDOKU_EDITION
  };

enum message_types
  {
    MSG_FINISH = 0,
    MSG_UNKNOWN
  };

static struct termios oldt;

static void restore_terminal_settings(void)
{
    tcsetattr(0, TCSANOW, &oldt);  /* Apply saved settings */
}

static void disable_waiting_for_enter(void)
{
    struct termios newt;

    /* Make terminal read 1 char at a time */
    tcgetattr(0, &oldt);  /* Save terminal settings */
    newt = oldt;  /* Init new settings */
    newt.c_lflag &= ~(ICANON | ECHO);  /* Change settings */
    tcsetattr(0, TCSANOW, &newt);  /* Apply settings */
    atexit(restore_terminal_settings); /* Make sure settings will be restored when program ends  */
}

int getInt();


class gui
{
 public:
  gui(std::string appVersion);
  ~gui();

  void initGui();
  
  int getOption();

  void imagineBadThings();

  void showInfo();
  void showGui();
  void showOptions();
  void clear(){clearScreen();};
  
  std::vector< std::vector<int> > askForValues();
  void showCurrent(std::vector< std::vector<std::string> > values,std::vector <std::string> status);
  void showCurrent(cell **myCells, std::vector <std::string> status);

  void showDescription();

  void draw_title();
  void draw_options(int state);
  void draw_map();
  void draw_info();

  void draw_cursor(int state);

  void eval_input();
  
  int isNotFinished(){return not_finished;};

  void print_message(char option, int msg_type);
  
 private:
  std::vector <std::string> vBadThings;
  std::string sVersion;
  std::vector<std::string> my_information;
  int gui_status;
  int not_finished;
  WINDOW *win_title;
  WINDOW *win_info;
  WINDOW *win_options;
  WINDOW *win_map;
};

#endif
