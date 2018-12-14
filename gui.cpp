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
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK); //colour for just solved cell
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

void gui::initGui(resolver*& my_resolver)
{
  gui_state = GUI_MAIN;
  //TITLE
  draw_title();
  //OPTIONS
  draw_options(gui_state);  
  //GAME MAP
  draw_map(gui_state,my_resolver);
  //information feedback
  draw_info();
  draw_cursor(gui_state,my_resolver);
  return;
}

void gui::show_gui(resolver*& my_resolver)
{
  draw_windows(gui_state,my_resolver);
  draw_cursor(gui_state,my_resolver);
  wrefresh(win_title);
  wrefresh(win_options);
  switch(gui_state)
    {
    case(GUI_RESOLVING_LOG):
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
void gui::draw_windows(int state, resolver*& my_resolver)
{
  int is_resized = win_resized();
  if(is_resized)
    {
      draw_title();
    }
  switch(state)
    {
    case(GUI_RESOLVING_LOG):
      draw_options(state);
      draw_info();
      draw_log(my_resolver);
      break;
    case(GUI_RESOLVING):
      iround = my_resolver->round();
    case(GUI_EDITION):
      draw_options(state);
      draw_info();
      draw_map(state,my_resolver);
      break;
    case(GUI_PLUGIN_MANAGEMENT):
      draw_options(state);
      draw_info();
      draw_plugins(my_resolver);
      break;
    default: //main window
      draw_options(state);
      draw_map(state,my_resolver);
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
    case(GUI_RESOLVING_LOG):
      mvwprintw(win_options,3,5,"[arrows] navigate");     
      ////quit
      mvwprintw(win_options,8,5,"[Q] Return for resolving");     
      break;
    case(GUI_RESOLVING):
      mvwprintw(win_options,3,5,"[r] resolve one round");
      mvwprintw(win_options,4,5,"[l] show log");      
      ////quit
      mvwprintw(win_options,8,5,"[Q] Return and cancel");     
      break;
    case(GUI_EDITION):
      mvwprintw(win_options,3,5,"[1-9] set this number to cell");
      mvwprintw(win_options,4,5,"[0] unset value of cell");      
      mvwprintw(win_options,5,5,"[arrow keys] select cell");
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

void gui::draw_map(int state, resolver*& my_resolver)
{
  win_map = newwin(22,COLS/2,1,(COLS/2));
  box(win_map, '|', '*');
  std::string title = "Your Sudoku:";
  if(state == GUI_RESOLVING)    
    title += "      ROUND " + std::to_string(iround);
  mvwprintw(win_map,1,2,title.c_str());
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
  print_values(my_resolver,((COLS/2)-35)/2, 3);
}

void gui::draw_plugins(resolver*& my_resolver)
{

  win_map = newwin(22,COLS/2,1,(COLS/2));
  box(win_map, '|', '*');

  std::string header = "Plugin No ";
  header += std::to_string(selected_plugin);
  header += ":";
  mvwprintw(win_map,1,2,header.c_str());

  if(selected_plugin)
    mvwprintw(win_map,11,1,"<");

  if(selected_plugin < (my_resolver->num_methods()-1))
    mvwprintw(win_map,11,(COLS/2 -2),">");
  if(selected_plugin >=0 && selected_plugin < my_resolver->num_methods())
    print_one_plugin(my_resolver,selected_plugin,3,3,20,COLS/2-2);
}
/*!function for printing resolving log*/
void gui::draw_log(resolver*& my_resolver)
{

  std::vector< std::string>::reverse_iterator reverse_iter;
  std::vector<std::string> field;
  std::vector<std::string>::iterator iter;
  int current_line = 1;
  int total_lines = 21; //TODO
  int field_line=0;
  
  win_map = newwin(22,COLS/2,1,(COLS/2)); //TODO, dynamic size
  box(win_map, '|', '*');

  std::vector< std::string> my_log = my_resolver->status();
  
  reverse_iter = my_log.rbegin();
  while(reverse_iter != my_log.rend() && current_line < total_lines)
    {
      field = ret_paragraph_with_lines_return(*reverse_iter,COLS/2-2,3);
      field_line = 0;
      for(iter = field.begin(); iter != field.end(); ++iter)
	{
	  current_line += field_line;
	  mvwprintw(win_map,current_line,1,iter->c_str());
	  field_line++;
	}
      current_line++;
      ++reverse_iter;
    }
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

void gui::draw_cursor(int state,resolver*& my_resolver)
{
  switch(state)
    {
    case(GUI_EDITION):
      {
	stcell_coordinates my_coordinates = my_resolver->cell_coordinates(selected_cell);
	wmove(win_map, my_coordinates.y,my_coordinates.x);
	keypad(win_info,FALSE);
	keypad(win_map,TRUE);
	break;
      }
    default:
      wmove(win_info,1,8);
      keypad(win_map,FALSE);
      keypad(win_info,TRUE);
      break;
    }
}

int gui::eval_keyboard_input(resolver*& my_resolver)
{
  int action_to_do = ACT_NONE;
  int option;
  /*when editing the cells map*/
  if(gui_state == GUI_EDITION)
    {
      option = wgetch(win_map);
      switch(option)
	{
	case('Q'):
	  //print_message('Q',MSG_CANCEL);
	  set_gui_state(GUI_MAIN);
	  break;
	case(KEY_LEFT):
	  move_left(my_resolver);	  
	  break;
	case(KEY_RIGHT):
	  move_right(my_resolver);	  
	  break;
	case(KEY_UP):
	  move_up(my_resolver);  
	  break;
	case(KEY_DOWN):
	  move_down(my_resolver);	  
	  break;
	case('0'):
	  set_value(my_resolver, 0);
	  break;
	case('1'):
	  set_value(my_resolver, 1);
	  break;	  
	case('2'):
	  set_value(my_resolver, 2);
	  break;
	case('3'):
	  set_value(my_resolver, 3);
	  break;	  
	case('4'):
	  set_value(my_resolver, 4);
	  break;
	case('5'):
	  set_value(my_resolver, 5);
	  break;
	case('6'):
	  set_value(my_resolver, 6);
	  break;
	case('7'):
	  set_value(my_resolver, 7);
	  break;
	case('8'):
	  set_value(my_resolver, 8);
	  break;
	case('9'):
	  set_value(my_resolver, 9);
	  break;
	default:
	  print_message(option,MSG_UNKNOWN);
	  break;
	}
    }
  //in plugin management screen
  else if (gui_state == GUI_PLUGIN_MANAGEMENT)
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
	  if(selected_plugin < (my_resolver->num_methods()-1))
	    selected_plugin++;	  
	  break;
	default:
	  print_message(option,MSG_UNKNOWN);
	  break;
	}
    }
  //in GUI resolving screen
  else if (gui_state == GUI_RESOLVING)
    {
      option = wgetch(win_info);
      switch(option)
	{
	case('l'):
	  set_gui_state(GUI_RESOLVING_LOG);
	  break;
	case('Q'):
	  //print_message('Q',MSG_CANCEL);
	  set_gui_state(GUI_MAIN);
	  break;
	case('r')://Resolve one round
	  action_to_do = ACT_RESOLVE_ROUND;
	  break;
	default:
	  print_message(option,MSG_UNKNOWN);
	  break;
	}
    }
  //in GUI resolving screen
  else if (gui_state == GUI_RESOLVING_LOG)
    {
      option = wgetch(win_info);
      switch(option)
	{
	case('Q'):
	  //print_message('Q',MSG_CANCEL);
	  set_gui_state(GUI_RESOLVING);
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
	  action_to_do = ACT_ASK_FOR_PLUGINS;
	  break;
	case('r'):
	  set_gui_state(GUI_RESOLVING);
	  iround=1;
	  break;
	default:
	  print_message(option,MSG_UNKNOWN);
	  break;
	}
    }
  return action_to_do;
}

void   gui::print_values(resolver*& my_resolver,int start_x, int start_y)
{
  int index = 0;
  int coordinate_x,coordinate_y;
  int value = 0;
  int possible_done = 0;
  
  coordinate_x = start_x;
  coordinate_y = start_y;
  for(int row = 1; row <= 9; row++)
    {
      for(int column = 1; column <= 9; column++)
	{
	  my_resolver->set_cell_coordinates(index,coordinate_x,coordinate_y);
	  my_resolver->set_cell_position(index,column,row);
	  value =  my_resolver->cell_value(index);
	  if(value)
	    mvwprintw(win_map,coordinate_y,coordinate_x,"%d",value);
	  else if(!possible_done)
	    {
	      //possible?
	      if(my_resolver->cell_has_sollution(index))
		{
		  my_resolver->cell_solve(index);
		  value =  my_resolver->cell_value(index);
		  if(value)
		    {
		      wattron(win_map,COLOR_PAIR(1));
		      mvwprintw(win_map,coordinate_y,coordinate_x,"%d",value);
		      wattroff(win_map,COLOR_PAIR(1));
		      possible_done = 1;
		    }
		}
	    }
	  coordinate_x+=4;
	  index++;
	}
      coordinate_y+=2;
      coordinate_x=start_x;
    }	
}

/*!print one plugin in map window, it return new coordinate y*/
int   gui::print_one_plugin(resolver*& my_resolver,int no_plugin,int coordinate_x, int coordinate_y ,int height, int width)
{
  std::vector<std::string> paragraph;
  std::vector<std::string>::iterator paragraph_iter;

  //NAME
  mvwprintw(win_map,coordinate_y,coordinate_x,"NAME:");
  coordinate_y++;
  paragraph.clear();
  paragraph = ret_paragraph_with_lines_return(my_resolver->method_name(no_plugin),width,3);
  
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
  paragraph = ret_paragraph_with_lines_return(my_resolver->method_description(no_plugin),width,5);
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
   paragraph = ret_paragraph_with_lines_return(my_resolver->method_status(no_plugin),width,5);
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
int  gui::move_left(resolver*& my_resolver)
{
  int ret = -1;
  stcell_position our_cell_position {-1,-1};
  //if not the first one, or out of bounds
  if(selected_cell > 0 && selected_cell < sudoku_size)
    {
      our_cell_position = my_resolver->cell_position(selected_cell);
      //if not in the left edge
      if(our_cell_position.col > 1)
	{
	  ret = selected_cell-1;
	  selected_cell = ret;
	}
    }
  return ret;
}

int  gui::move_right(resolver*& my_resolver)
{
  int ret = -1;
  stcell_position our_cell_position {-1,-1};
  //if not the last one, or out of bounds
  if(selected_cell >= 0 && selected_cell < (sudoku_size-1))
    {
      our_cell_position = my_resolver->cell_position(selected_cell);
      //if not in the right edge
      if(our_cell_position.col < 9)
	{
	  ret = selected_cell+1;
	  selected_cell = ret;
	}
    }
  return ret;
}

int  gui::move_up(resolver*& my_resolver)
{
  int ret = -1;
  stcell_position our_cell_position {-1,-1};
  //if not in the first row, or out of bounds
  if(selected_cell > 8 && selected_cell < sudoku_size)
    {
      our_cell_position = my_resolver->cell_position(selected_cell);
      //if not in the upper edge
      if(our_cell_position.row > 1)
	{
	  ret = selected_cell-9;
	  selected_cell = ret;
	}
    }
  return ret;
}

int  gui::move_down(resolver*& my_resolver)
{
  int ret = -1;
  stcell_position our_cell_position {-1,-1};
  //if not in the first row, or out of bounds
  if(selected_cell >= 0 && selected_cell <= (sudoku_size-10))
    {
      our_cell_position = my_resolver->cell_position(selected_cell);      
      //if not in the bottom edge
      if(our_cell_position.row < 9)
	{
	  ret = selected_cell+9;
	  selected_cell = ret;
	}
    }
  return ret;

}

int gui::set_value(resolver*& my_resolver, int value)
{
  int ret = -1;
  std::string message;
  if(value >=0 && value <=9)
    {
      if(value == 0)
	{
	  ret=0;
	  my_resolver->set_cell_value(selected_cell,value);
	  //print_message("value to 0");
	}
      else
	{
	  message = "cell ";
	  message += std::to_string(selected_cell);
	  message += " val ";
	  message += std::to_string(value);

	  ret =  my_resolver->value_possible(selected_cell,value);
	  if(ret > 0)
	    {
	      message += "... possible!";
	      my_resolver->set_cell_value(selected_cell,value);
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
  gui_state = state;
  //OPTIONS
  draw_options(gui_state);
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
