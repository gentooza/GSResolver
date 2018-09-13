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

#include "gui.h"

int getInt(){
	int x = 0;
	
	while(!(std::cin >> x)){
	  std::cin.clear();
	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	  std::cout << "Invalid input.  Try again: ";
	}
	if(x < 0 || x > 9)
	  x =-1;
	
	return x;
}


gui::gui(std::string appVersion)
{
  initscr();
  noecho();
  imagineBadThings();
  sVersion = appVersion;
  win_title = NULL;
  win_info = NULL;
  win_options = NULL;
  win_map = NULL;
  not_finished=1;
  return;
}
gui::~gui()
{
  endwin();
  return;
}

void gui::imagineBadThings()
{
  vBadThings.clear();

  vBadThings.push_back("It could jump out your screen and kill your cat!");
  vBadThings.push_back("It could slap your mum and dad with a rotten fish!");
  vBadThings.push_back("It could leave you to begin a promising career as Ubuntu Touch developer!");
  vBadThings.push_back("It could sing you an Enrique Iglesia's song!");
  vBadThings.push_back("It could spy you for the NSA!");
  vBadThings.push_back("It could show all your pornographic content in your facebook!");
  vBadThings.push_back("It could ban you from tweeter");  
  //...
}

void gui::showInfo()
{
  printw("Welcome to gentooza's sudoku resolver, version: %s !",sVersion.c_str());
  mvprintw(2,0,"This program is Free (libre) software developed under the GPLv3+");
  srand ( time(NULL) );
  std::string text = vBadThings.at(rand() % vBadThings.size());
  mvprintw(4,0,"It's offered with a lot of love and no warranties at all, it could never solve your fuc$%/= sudoku, or worse! %s \nIt's interesting as an experiment for plugins programming, you can add different algorithms easily for solving your sudokus \n\n<PRESS ANY KEY TO CONTINUE>",text.c_str());

  refresh();
  getch();
}

void gui::initGui(cell **& cells_map)
{
  gui_status = GUI_MAIN;
  //TITLE
  draw_title();
  //OPTIONS
  draw_options(gui_status);  
  //GAME MAP
  draw_map(cells_map);
  //information feedback
  draw_info();
  draw_cursor(gui_status,cells_map);
  return;
}

void gui::showGui(cell **& my_cells)
{
  draw_cursor(gui_status,my_cells);
  wrefresh(win_title);
  wrefresh(win_options);
  switch(gui_status)
    {
    case(GUI_EDITION):
      wrefresh(win_info);
      wrefresh(win_map);
      break;
    default:
      wrefresh(win_map);
      wrefresh(win_info);
      break;
    };
  return;
}

void gui::draw_title()
{
  win_title = newwin(1,COLS,0,0);
  std::string title = "*** Gentooza\'s sudokus resolver, version: ";
  title += sVersion;
  title += " ***";
  box(win_title, 0 , 0);
  mvwprintw(win_title,0,(COLS-title.length())/2,title.c_str());
}

void gui::draw_options(int state)
{
  win_options = newwin(11,COLS/2,1,0);
  box(win_options, '|', '*');
  mvwprintw(win_options,1,2,"Options:");

  switch(state)
    {
    case(GUI_EDITION):
      mvwprintw(win_options,4,5,"[1-9] set this number to cell");
      mvwprintw(win_options,5,5,"[arrow keys] select cell");
      ////quit
      mvwprintw(win_options,8,5,"[Q] Cancel   [S] Save");
      break;
    default:
      mvwprintw(win_options,4,5,"[e] Edit your sudoku");
      ////quit
      mvwprintw(win_options,8,5,"[Q] Quit GSResolver");
      break;
    }
}

void gui::draw_map(cell **& cells_map)
{
  win_map = newwin(22,COLS/2,1,(COLS/2));
  box(win_map, '|', '*');
  mvwprintw(win_map,1,2,"Your Sudoku:");
  mvwhline(win_map,4, ((COLS/2)-36)/2,'-',33);
  mvwhline(win_map,6, ((COLS/2)-36)/2,'-',33);
  mvwhline(win_map,8, ((COLS/2)-36)/2,'=',33);
  mvwhline(win_map,10, ((COLS/2)-36)/2,'-',33);
  mvwhline(win_map,12, ((COLS/2)-36)/2,'-',33);
  mvwhline(win_map,14, ((COLS/2)-36)/2,'=',33);
  mvwhline(win_map,16, ((COLS/2)-36)/2,'-',33);
  mvwhline(win_map,18, ((COLS/2)-36)/2,'-',33);
  mvwvline(win_map,3, 4,'|',17);
  mvwvline(win_map,3, 8,'|',17);
  mvwvline(win_map,3, 12,'I',17);
  mvwvline(win_map,3, 16,'|',17);
  mvwvline(win_map,3, 20,'|',17);
  mvwvline(win_map,3, 24,'I',17);
  mvwvline(win_map,3, 28,'|',17);
  mvwvline(win_map,3, 32,'|',17);
  print_values(cells_map,2, 3);
}

void gui::draw_info()
{
  std::vector<std::string>::reverse_iterator iter;
  
  win_info = newwin(11,COLS/2,12,0);
  box(win_info, '|', '*');
  mvwprintw(win_info,1,2,"Info:");
  int i = 0;
  for (iter = my_information.rbegin(); iter != my_information.rend() && i < 6; ++iter)
    {
      mvwprintw(win_info,3+i,4,iter->c_str());
      i++;
    }

}

void gui::draw_cursor(int state,cell **& my_cells)
{
  switch(state)
    {
    case(GUI_EDITION):
      wmove(win_map, my_cells[selected_cell]->ret_y(),my_cells[selected_cell]->ret_x());
      keypad(win_map,TRUE);
      selected_cell=1;
      break;
    default:
      wmove(win_info,1,8);
      keypad(win_map,FALSE);    
      break;
    }
}

int gui::eval_keyboard_input(cell ** map_cells)
{
  int action_to_do = 0;
  int option;
  /*when editing the cells map*/
  if(gui_status == GUI_EDITION)
    {
      option = wgetch(win_map);
      switch(option)
	{
	case('Q'):
	  print_message('Q',MSG_CANCEL);
	  set_gui_main();
	  break;
	case(KEY_LEFT):
	  move_left(map_cells);	  
	  break;
	case(KEY_RIGHT):
	  move_right(map_cells);	  
	  break;
	case(KEY_UP):
	  move_up(map_cells);  
	  break;
	case(KEY_DOWN):
	  move_down(map_cells);	  
	  break;
	default:
	  print_message(option,MSG_UNKNOWN);
	  draw_info();
	  break;
	}
    }
  /*at main screen*/
  else
    {
      option = wgetch(win_info);
      switch(option)
	{
	case('Q'):
	  not_finished=0;
	  print_message('Q',MSG_FINISH);
	  draw_info();
	  break;
	case('e'):
	  print_message('e',MSG_EDITION);
	  set_gui_edition();
	  break;
	default:
	  print_message(option,MSG_UNKNOWN);
	  draw_info();
	  break;
	}
    }
  return action_to_do;
}

void   gui::print_values(cell **& cells_map,int start_x, int start_y)
{
  int index = 0;
  int coordinate_x,coordinate_y;
  
  coordinate_x = start_x;
  coordinate_y = start_y;
  for(int row = 1; row <= 9; row++)
    {
      for(int column = 1; column <= 9; column++)
	{
	  cells_map[index]->setCoordinates(coordinate_x,coordinate_y);
	  if(cells_map[index]->retValue())
	    mvwprintw(win_map,coordinate_y,coordinate_x,"%d",cells_map[index]->retValue());
	  coordinate_x+=4;
	  index++;
	}
      coordinate_y+=2;
    }	
}

void gui::print_message(char option, int msg_type)
{
  std::string new_message;

  switch(msg_type)
    {
    case(MSG_FINISH):
      new_message = option;
      new_message += " - ";
      new_message +="Closing, thanks for using GSResolver!";
      break;
    case(MSG_CANCEL):
      new_message = option;
      new_message += " - ";
      new_message +="Canceled!";
      break;
    case(MSG_EDITION):
      new_message = option;
      new_message += " - ";
      new_message +="going to sudoku edition!";
      break;
    default:
      new_message = option;
      new_message += " - ";
      new_message +="Sorry! Unknown option";
      break;
    };
  my_information.push_back(new_message);
  while(my_information.size()>6)
    my_information.erase(my_information.begin());

  return;

}

//actions on cells functions
int  gui::move_left(cell **&cells_map)
{
  int ret = -1;
  int my_col;
  //if not the first one, or out of bounds
  if(selected_cell > 0 && selected_cell < 81)
    {
      my_col = cells_map[selected_cell]->ret_col();
      //if not in the left edge
      if(my_col > 1)
	{
	  ret = selected_cell-1;
	  selected_cell = ret;
	}
    }
  return ret;
}

int  gui::move_right(cell **&cells_map)
{
  int ret = -1;
  int my_col;
  //if not the last one, or out of bounds
  if(selected_cell >= 0 && selected_cell < 80)
    {
      my_col = cells_map[selected_cell]->ret_col();
      //if not in the right edge
      if(my_col < 9)
	{
	  ret = selected_cell+1;
	  selected_cell = ret;
	}
    }
  return ret;
}

int  gui::move_up(cell **&cells_map)
{
  int ret = -1;
  int my_row;
  //if not in the first row, or out of bounds
  if(selected_cell > 8 && selected_cell < 81)
    {
      my_row = cells_map[selected_cell]->ret_row();
      //if not in the upper edge
      if(my_row > 1)
	{
	  ret = selected_cell-9;
	  selected_cell = ret;
	}
    }
  return ret;
}

int  gui::move_down(cell **&cells_map)
{
  int ret = -1;
  int my_row;
  //if not in the first row, or out of bounds
  if(selected_cell >= 0 && selected_cell <= 71)
    {
      my_row = cells_map[selected_cell]->ret_row();
      //if not in the bottom edge
      if(my_row < 9)
	{
	  ret = selected_cell+9;
	  selected_cell = ret;
	}
    }
  return ret;

}

int gui::set_value(cell **&cells_map, int value)
{
  return 0;
}
////////////////


void gui::set_gui_main()
{
  gui_status = GUI_MAIN;
  //OPTIONS
  draw_options(gui_status);
  //information feedback
  draw_info();
  //draw_cursor(gui_status);
}
void gui::set_gui_edition()
{
  gui_status = GUI_EDITION;
  //OPTIONS
  draw_options(gui_status);
  //information feedback
  draw_info();
  //draw_cursor(gui_status);
}
