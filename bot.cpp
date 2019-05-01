/*
Author: Robert Bangiyev
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 3A
Date: April 27, 2019

This code is what tells the dwarf what to do. I fix it to make the dwarf be more efficient at collecting lumber.
*/
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"
#include <cmath>

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS;  // global variables
int COLS;
int NUM;

/* onStart: 
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do 
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << endl; // Print a greeting message

  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;
}
//distance formula to make it so the dwarf goes to the nearest tree
int distance(int a, int b, int a2, int b2)
{
	return sqrt(pow(a - a2, 2) + pow(b - b2, 2));
}
//bool function to see if the space is next to a tree
bool isNextToATree(Dwarf & dwarf, int r, int c)
{
	if ((dwarf.look(r - 1, c) == PINE_TREE || dwarf.look(r + 1, c) == PINE_TREE || dwarf.look(r, c - 1) == PINE_TREE || dwarf.look(r, c + 1) == PINE_TREE) && dwarf.look(r, c) == EMPTY)
		return true;
	else if ((dwarf.look(r - 1, c) == APPLE_TREE || dwarf.look(r + 1, c) == APPLE_TREE || dwarf.look(r, c - 1) == APPLE_TREE || dwarf.look(r, c + 1) == APPLE_TREE) && dwarf.look(r, c) == EMPTY)
		return true;
	else
		return false;
}
//function to see closest row
int closestrow(Dwarf &dwarf)
{
	int r = dwarf.row();
	int c = dwarf.col();
	int dist = 10000;
	int goodrow=0;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (isNextToATree(dwarf, i, j))
			{
				if (distance(r, c, i, j) < dist)
				{
					dist = distance(r, c, i, j);
					goodrow = i;
				}
			}
		}
	}
	return goodrow;
}
//function to see closest column
int closestcol(Dwarf &dwarf)
{
	int r = dwarf.row();
	int r2 = closestrow(dwarf);
	int c = dwarf.col();
	int dist = 10000;
	int colout = 0;
	for (int i = 0; i < COLS; i++)
	{
		if (isNextToATree(dwarf, r2, i))
		{
			if (distance(r, c, r2, i) < dist)
			{
				dist = distance(r, c, r2, i);
				colout = i;
			}
		}
	}
	return colout;
}


/* onAction: 
A procedure called each time an idle dwarf is choosing 
their next action.
Parameters:
    dwarf:   dwarf choosing an action
    day:     day (1+)
    hours:   number of hours in 24-hour format (0-23)
    minutes: number of minutes (0-59)
    log:     a cout-like log  */

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();

  // Look if there is a tree on the right from the dwarf
  if (dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c + 1) == APPLE_TREE) {
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(EAST);
    return;
  }
  if (dwarf.look(r, c - 1) == PINE_TREE || dwarf.look(r, c - 1) == APPLE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(WEST);
	  return;
  }
  if (dwarf.look(r + 1, c) == PINE_TREE || dwarf.look(r + 1, c) == APPLE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(SOUTH);
	  return;
  }
  if (dwarf.look(r - 1,c) == PINE_TREE || dwarf.look(r - 1, c) == APPLE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(NORTH);
	  return;
  }
  else {
    int rr = closestrow(dwarf);
    int cc = closestcol(dwarf);
    log << "Walk to " << rr << " " << cc << endl;
    dwarf.start_walk(rr, cc);
    return;
  }
}