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

void gui::show_gui(cell **& my_cells,std::vector<struct method_info> information)
{
  draw_windows(gui_status,my_cells,information);
  draw_cursor(gui_status,my_cells);
  wrefresh(win_title);
  wrefresh(win_options);
  switch(gui_status)
    {
    case(GUI_PLUGIN_MANAGEMENT):
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
void gui::draw_windows(int status, cell **& my_cells, std::vector<struct method_info> information)
{
  int is_resized = win_resized();
  if(is_resized)
    {
      draw_title();
    }
  switch(gui_status)
    {
    case(GUI_RESOLVING):
    case(GUI_EDITION):
      draw_options(status);
      draw_info();
      draw_map(my_cells);
      break;
    case(GUI_PLUGIN_MANAGEMENT):
      draw_options(status);
      draw_info();
      draw_plugins(information);
      break;
    default: //main window
      draw_options(status);
      draw_map(my_cells);
      draw_info();
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
    case(GUI_RESOLVING):
      mvwprintw(win_options,3,5,"[r] resolve one round");
      mvwprintw(win_options,4,5,"[R] resolve everything");
      ////quit
      mvwprintw(win_options,8,5,"[Q] Return");     
      break;
    case(GUI_EDITION):
      mvwprintw(win_options,3,5,"[1-9] set this number to cell");
      mvwprintw(win_options,4,5,"[arrow keys] select cell");
      ////quit
      mvwprintw(win_options,8,5,"[Q] Return");
      break;
    case(GUI_PLUGIN_MANAGEMENT):
      mvwprintw(win_options,3,5,"[<- ->arrow keys] navigate methods");
      //mvwprintw(win_options,4,5,"[1-100] change usage order position");
      //mvwprintw(win_options,5,5,"[l] reload method");
      //mvwprintw(win_options,6,5,"[u] unload method");     
      ////quit
      mvwprintw(win_options,8,5,"[Q] Return");
      break;
    default:
      mvwprintw(win_options,3,5,"[e] Edit your sudoku");
      mvwprintw(win_options,4,5,"[p] Manage resolve methods");
      mvwprintw(win_options,5,5,"[r] ¡Resolve!");           
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
  mvwvline(win_map,3, ((COLS/2)-31)/2,'|',17);
  mvwvline(win_map,3, ((COLS/2)-23)/2,'|',17);
  mvwvline(win_map,3, ((COLS/2)-15)/2,'I',17);
  mvwvline(win_map,3, ((COLS/2)-7)/2,'|',17);
  mvwvline(win_map,3, ((COLS/2)+1)/2,'|',17);
  mvwvline(win_map,3, ((COLS/2)+9)/2,'I',17);
  mvwvline(win_map,3, ((COLS/2)+17)/2,'|',17);
  mvwvline(win_map,3, ((COLS/2)+25)/2,'|',17); //32
  print_values(cells_map,((COLS/2)-35)/2, 3);
}

void gui::draw_plugins(std::vector<struct method_info> information)
{

  win_map = newwin(22,COLS/2,1,(COLS/2));
  box(win_map, '|', '*');

  std::string header = "Plugin No ";
  header += std::to_string(selected_plugin);
  header += ":";
  mvwprintw(win_map,1,2,header.c_str());

  if(selected_plugin)
    mvwprintw(win_map,11,1,"<");

  if(selected_plugin < (information.size()-1))
    mvwprintw(win_map,11,(COLS/2 -2),">");
  if(selected_plugin >=0 && selected_plugin < information.size())
    print_one_plugin(information[selected_plugin],3,3,20,COLS/2-2);
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
      keypad(win_info,FALSE);
      keypad(win_map,TRUE);
      break;
    default:
      wmove(win_info,1,8);
      keypad(win_map,FALSE);
      keypad(win_info,TRUE);
      break;
    }
}

int gui::eval_keyboard_input(cell ** cells_map,std::vector<struct method_info> information)
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
	  //print_message('Q',MSG_CANCEL);
	  set_gui_state(GUI_MAIN);
	  break;
	case(KEY_LEFT):
	  move_left(cells_map);	  
	  break;
	case(KEY_RIGHT):
	  move_right(cells_map);	  
	  break;
	case(KEY_UP):
	  move_up(cells_map);  
	  break;
	case(KEY_DOWN):
	  move_down(cells_map);	  
	  break;
	case('0'):
	  set_value(cells_map, 0);
	  break;
	case('1'):
	  set_value(cells_map, 1);
	  break;	  
	case('2'):
	  set_value(cells_map, 2);
	  break;
	case('3'):
	  set_value(cells_map, 3);
	  break;	  
	case('4'):
	  set_value(cells_map, 4);
	  break;
	case('5'):
	  set_value(cells_map, 5);
	  break;
	case('6'):
	  set_value(cells_map, 6);
	  break;
	case('7'):
	  set_value(cells_map, 7);
	  break;
	case('8'):
	  set_value(cells_map, 8);
	  break;
	case('9'):
	  set_value(cells_map, 9);
	  break;
	default:
	  print_message(option,MSG_UNKNOWN);
	  break;
	}
    }
  //in plugin management screen
  else if (gui_status == GUI_PLUGIN_MANAGEMENT)
    {
      option = wgetch(win_info);
      switch(option)
	{
	case('Q'):
	  //print_message('Q',MSG_CANCEL);
	  set_gui_state(GUI_MAIN);
	  break;
	case(KEY_LEFT):
	  if(selected_plugin)
	    selected_plugin--;	  
	  break;
	case(KEY_RIGHT):
	  if(selected_plugin< (information.size()-1))
	    selected_plugin++;	  
	  break;
	default:
	  print_message(option,MSG_UNKNOWN);
	  break;
	}
    }
  //in GUI resolving screen
  else if (gui_status == GUI_RESOLVING)
    {
      option = wgetch(win_info);
      switch(option)
	{
	case('Q'):
	  //print_message('Q',MSG_CANCEL);
	  set_gui_state(GUI_MAIN);
	  break;
	default:
	  print_message(option,MSG_UNKNOWN);
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
	  //print_message('Q',MSG_FINISH);
	  break;
	case('e'):
	  //print_message('e',MSG_EDITION);
	  set_gui_state(GUI_EDITION);
	  break;
	case('p'):
	  //print_message('p',MSG_PLUGIN_MANAGEMENT);
	  set_gui_state(GUI_PLUGIN_MANAGEMENT);
	  selected_plugin=0;
	  action_to_do = GUI_PLUGIN_MANAGEMENT;
	  break;
	case('r'):
	  set_gui_state(GUI_RESOLVING);
	default:
	  print_message(option,MSG_UNKNOWN);
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
	  cells_map[index]->set_coordinates(coordinate_x,coordinate_y);
	  cells_map[index]->set_position(column,row);
	  if(cells_map[index]->ret_value())
	    mvwprintw(win_map,coordinate_y,coordinate_x,"%d",cells_map[index]->ret_value());
	  coordinate_x+=4;
	  index++;
	}
      coordinate_y+=2;
      coordinate_x=start_x;
    }	
}

/*!print one plugin in map window, it return new coordinate y*/
int   gui::print_one_plugin(struct method_info method,int coordinate_x, int coordinate_y ,int height, int width)
{
  std::vector<std::string> paragraph;
  std::vector<std::string>::iterator paragraph_iter;

  //NAME
  mvwprintw(win_map,coordinate_y,coordinate_x,"NAME:");
  coordinate_y++;
  paragraph.clear();
  paragraph = ret_paragraph_with_lines_return(method.name,width,3);
  
  for(paragraph_iter = paragraph.begin(); paragraph_iter != paragraph.end(); ++paragraph_iter)
    {
      mvwprintw(win_map,coordinate_y,coordinate_x,paragraph_iter->c_str());
      coordinate_y++;
    }
  coordinate_y++;
  coordinate_y++;
  
  //DESCRIPTION
  mvwprintw(win_map,coordinate_y,coordinate_x,"DESCRIPTION:");
  coordinate_y++;
  paragraph.clear();
  paragraph = ret_paragraph_with_lines_return(method.description,width,5);
  for(paragraph_iter = paragraph.begin(); paragraph_iter != paragraph.end(); ++paragraph_iter)
    {
      mvwprintw(win_map,coordinate_y,coordinate_x,paragraph_iter->c_str());
      coordinate_y++;
    }
  coordinate_y++;
  coordinate_y++;
  
  //STATUS
   mvwprintw(win_map,coordinate_y,coordinate_x,"STATUS:");
   coordinate_y++;
   paragraph.clear();
   paragraph = ret_paragraph_with_lines_return(method.status,width,5);
   for(paragraph_iter = paragraph.begin(); paragraph_iter != paragraph.end(); ++paragraph_iter)
     {
      mvwprintw(win_map,coordinate_y,coordinate_x,paragraph_iter->c_str());
      coordinate_y++;
    }


  return coordinate_y;
}

void gui::print_message(std::string text)
{

  my_information.push_back(text);
  while(my_information.size()>6)
    my_information.erase(my_information.begin());

  return;

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
    case(MSG_PLUGIN_MANAGEMENT):
      new_message = option;
      new_message += " - ";
      new_message +="going to resolve methods system!";
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
  int ret = -1;
  std::string message;
  if(value >=0 && value <=9)
    {
      if(value == 0)
	{
	  ret=0;
	  cells_map[selected_cell]->set_value(value);
	  //print_message("value to 0");
	}
      else
	{
	  message = "cell ";
	  message += std::to_string(selected_cell);
	  message += " val ";
	  message += std::to_string(value);

	  ret = tools_value_possible(cells_map,selected_cell,value);
	  if(ret > 0)
	    {
	      message += "... possible!";
	      cells_map[selected_cell]->set_value(value);
	      ret=0;
	    }
	  else
	    {
	      if(ret == 0)
		message += "... not possible! value 0";
	      else if(ret == -1)
		message += "... not possible! section!";
	      else if(ret == -2)
		message += "... not possible! row!";
	      else if(ret == -3)
		message += "... not possible! column!";
	      else
		message += "... not possible! unknown!";
	    }
	  print_message(message);
	}
    }
  return ret;
}
////////////////

void gui::set_gui_state(int state)
{
  gui_status = state;
  //OPTIONS
  draw_options(gui_status);
  //information feedback
  draw_info();
}

int gui::win_resized()
{
  int ret = 0;
  if(last_COLS != COLS || last_LINES != LINES)
    {
      ret = 1;
      last_COLS = COLS;
      last_LINES = LINES;
    }

  return ret;
}
