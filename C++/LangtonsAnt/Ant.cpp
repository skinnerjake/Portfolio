/*********************************************************************
Name: 			Jacob Skinner
Date:			10/5/16
Description:	This file contains the definitions for methods of 
				class Ant.
*********************************************************************/

#include "Ant.hpp"

/********************************************************************
Description:	Constructor for an object of class Ant
********************************************************************/

Ant::Ant(int r, int c, Board *b)
{
	setRow(r);
	setCol(c);
	area = b;
	facing = UP;
}


void Ant::setRow(int r)
{
	row = r;
}

void Ant::setCol(int c)
{
	col = c;
}

int Ant::getRow()
{
	return row;
}


int Ant::getCol()
{
	return col;
}

int Ant::getSteps()
{
	return steps;
}

void Ant::setSteps(int s)
{
	steps = s;
}

/********************************************************************
Description:	This method will move the location of the ant one
				space, depending on which way it is facing. It uses
				the wrap board function to make sure the ant is still
				on the board. It also updates the color of the 
				original and new squares. Lastly, this function
				utilizes the turnAnt function to turn it clockwise or
				counterclockwise based on the color of the square on 
				which it is located.
********************************************************************/
void Ant::moveAnt()
{
	area->changeColor(row, col);
	switch (facing)
	{
		case UP: row -= 1;
			break;
		case RIGHT: col += 1;
			break;
		case DOWN: row += 1;
			break;
		case LEFT: col -= 1;
			break;
	}
	wrapBoard();
	area->changeColor(row, col);
	turnAnt();
}

/********************************************************************
Description:	This method turns the ant clockwise or
				counterclockwise based on the color of the square on 
				which it is located. 
********************************************************************/
void Ant::turnAnt()
{
	if (area->getColor(row, col) == ANT_BLACK)
		switch (facing)
		{
			case UP: facing = LEFT;
				break;
			case RIGHT: facing = UP;
				break;
			case DOWN: facing = RIGHT;
				break;
			case LEFT: facing = DOWN;
				break;
		}
	else if (area->getColor(row, col) == ANT_WHITE)
		switch (facing)
		{
			case UP: facing = RIGHT;
				break;
			case RIGHT: facing = DOWN;
				break;
			case DOWN: facing = LEFT;
				break;
			case LEFT: facing = UP;
				break;
		}
}

/********************************************************************
Description:	This method moves the ant's location across the board
				if its location is out of the bounds of the array.
********************************************************************/
void Ant::wrapBoard()
{
	if (row < 0)
		row = area->getRow() - 1;
	else if (row == area->getRow())
		row = 0;

	if (col < 0)
		col = area->getCol() - 1;
	else if (col == area->getCol())
		col = 0;
}