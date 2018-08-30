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
  imagineBadThings();
  disable_waiting_for_enter();
  sVersion = appVersion;
  return;
}
gui::~gui()
{
  return;
}

int gui::getOption()
{
   int ch = 0;
   ch = getchar();
   if (ch == 'r') //resolve round
     clearScreen();
   else if (ch =='R') //resolve all
       clearScreen();
   else if(ch == 'v')
       clearScreen();
   else if (ch == 'Q')
     {
       std::cout << std::endl;
       std::cout << "Thanks for using Gentooza's Sudokus Resolver, have a very nice day!" << std::endl;
     }
   else if (ch =='s')
     clearScreen();
   //   else if(ch == 'c') TODO CHANGE
   else
     {
       ch = 'x';
     }

   return ch;
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

std::vector< std::vector<int> >  gui::askForValues()
{
  int value;
  std::vector< std::vector<int> > ourSudoku;
  std::vector<int> row;
  std::vector< std::vector<int> >::iterator ourSudokuIter;
  std::vector<int>::iterator rowIter;  

  std::cout << "*********************************************************************************" << std::endl;

  for(int i=1; i<10;i++)
    {
      row.clear();
      for(int j=1; j<10;j++)
	{
	  std::cout <<"Insert value ("<<i<<","<<j<<"):"<<std::endl;
	  value = getInt();
	  while(value <0)
	    {
	      std::cout <<"Insert value ("<<i<<","<<j<<"), please a value between 1 and 9, or 0 if empty:"<<std::endl;
	      value = getInt();
	    }
	  row.push_back(value);
	  clearScreen();
	  std::cout << "inserted value:" << value << std::endl;
	  std::cout << "*********************************************************************************" << std::endl;
	  if(ourSudoku.size()>0)
	    {
	      for(ourSudokuIter = ourSudoku.begin(); ourSudokuIter != ourSudoku.end(); ++ourSudokuIter)
		{
		  for(rowIter = ourSudokuIter->begin(); rowIter != ourSudokuIter->end(); ++rowIter)
		    {
		      if(*rowIter != 0)
			std::cout << *rowIter;
		      else
			std::cout << " ";
		      std::cout << "        ";
		    }
		  std::cout << std::endl;
		}
	    }
	  for(rowIter = row.begin(); rowIter != row.end(); ++rowIter)
	    {
	      if(*rowIter != 0)
		std::cout << *rowIter;
	      else
		std::cout << " ";
	      std::cout << "        ";
	    }
	  std::cout << std::endl;	  
	}
      ourSudoku.push_back(row);
    }
  
  return ourSudoku;
}

void gui::showCurrent(std::vector< std::vector<std::string> > values,std::vector <std::string> status)
{
  std::vector< std::vector<std::string> >::iterator rowIter;
  std::vector<std::string>::iterator fieldIter;
  
  std::cout <<"*********************************************************************************" << std::endl;
  std::cout<<std::endl;
  for(fieldIter = status.begin(); fieldIter != status.end(); ++fieldIter)
    std::cout << *fieldIter << std::endl;
  std::cout<<std::endl;
  for(rowIter = values.begin(); rowIter != values.end(); ++rowIter)
    {
      for(fieldIter = rowIter->begin(); fieldIter != rowIter->end(); ++fieldIter)
	{
	  std::cout << " ";
	  std::cout << *fieldIter;
	  std::cout << " |";
	}
      std::cout << "|" << std::endl;
    }
  std::cout <<"*********************************************************************************" << std::endl;
}

void gui::showCurrent(cell **myCells, std::vector <std::string> status)
{
  int i,j;
  int index = 0;
  std::vector<std::string>::iterator fieldIter;
  std::vector <int>::iterator couldBeIter;
  std::vector <int> cellCouldBe;
  const int space = 9;
  int currentSpace = 0;
  std::cout <<"*****************************************************************************************" << std::endl;
  std::cout<<std::endl;
  for(fieldIter = status.begin(); fieldIter != status.end(); ++fieldIter)
    std::cout << *fieldIter << std::endl;
  std::cout<<std::endl;
  for(i = 0; i < ROWS; i++)
    {
      for(j= 0; j < COLUMNS; j++)
	{
	  if(index < sudoku_size)
	    {
	      currentSpace = 0;
	      if(!myCells[index]->retDefined())
		{
		  cellCouldBe = myCells[index]->retCouldBe();
		  if(myCells[index]->hasSollution())
		    {
		      std::cout << "(";
		      currentSpace++;
		    }
		  for(couldBeIter = cellCouldBe.begin(); couldBeIter != cellCouldBe.end(); ++couldBeIter)
		    {
		      std::cout << std::to_string(*couldBeIter);
		      currentSpace++;
		    }
		  if(myCells[index]->hasSollution())
		    {
		      std::cout << ")";
		      currentSpace++;
		    }
		}
	      else
		{
		  currentSpace++;
		  std::cout << std::to_string(myCells[index]->retValue());
		}
	      while(currentSpace <= space)
		{
		  std::cout << " ";
		  currentSpace++;
		}
	    }
	  index++;
	}
      std::cout << std::endl;
      j = 0;
    }
  std::cout <<"*****************************************************************************************" << std::endl;
}
void gui::showInfo()
{
  std::cout << "Welcome to gentooza's sudoku resolver, version: " << sVersion << "!" << std::endl;
  std::cout << "this program is Free (libre) software developed under the GPLv3+" << std::endl;
  std::cout << "it's offered with a lot of love and no warranties at all, it could never solve your fuc$%/= sudoku, or worse! ";
  std::string text = vBadThings.at(rand() % vBadThings.size());
  std::cout << text << std::endl;
  std::cout << "it's interesting as an experiment for plugins programming, you can add different algorithms easily for solving your sudokus" << std::endl;
}

void gui::showOptions()
{
  std::cout << "-> Press 'r' to solve one round" << std::endl;
  std::cout << "-> Press 'R' to solve everything at once" << std::endl;
  std::cout << "-> Press 'v' to show program's info and version" << std::endl;
  std::cout << "-> Press 'Q' to quit" << std::endl;  
}

