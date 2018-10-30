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
#include "tools.h"

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
  OPT_INVALID = 'x',
  OPT_EDITION = 'e',
  OPT_PLUGIN_MANAGEMENT = 'p'
};

enum gui_status
  {
    GUI_MAIN = 0,
    GUI_EDITION,
    GUI_PLUGIN_MANAGEMENT
  };

enum message_types
  {
    MSG_FINISH = 0,
    MSG_UNKNOWN,
    MSG_CANCEL,
    MSG_EDITION,
    MSG_PLUGIN_MANAGEMENT
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

  void initGui(cell**& cells_map);
  
  int getOption();

  void imagineBadThings();

  void showInfo();
  void showGui(cell **& my_cells);

  void showDescription();

  void draw_title();
  void draw_options(int state);
  void draw_map(cell **& cells_map);
  void draw_info();

  void draw_cursor(int state,cell **& my_cells);

  int eval_keyboard_input( cell ** map_cells);
  
  int isNotFinished(){return not_finished;};

  void print_message(std::string text);
  void print_message(char option, int msg_type);
  void print_values(cell **& cells_map,int start_x, int start_y);

  //ACTIONS ON CELLS
  int  move_left(cell **&cells_map);
  int  move_right(cell **&cells_map);
  int  move_up(cell **&cells_map);
  int  move_down(cell **&cells_map);
  int  set_value(cell **&cells_map, int value);
  //

  //////////////////////////////////////////////
  //  changing states
  void set_gui_state(int state);
  
 private:
  std::vector <std::string> vBadThings;
  std::string sVersion;
  std::vector<std::string> my_information;
  int gui_status;
  int not_finished;
  int selected_cell;
  WINDOW *win_title;
  WINDOW *win_info;
  WINDOW *win_options;
  WINDOW *win_map;
};

#endif
