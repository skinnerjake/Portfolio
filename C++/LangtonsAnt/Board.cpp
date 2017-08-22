/*********************************************************************
Name: 			Jacob Skinner
Date:			10/5/16
Description:	This file contains the definitions for methods of 
				class Board.
*********************************************************************/

#include "Board.hpp"
#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

/********************************************************************
Description:	Constructor for an object of class Board. Initializes
				row, col, and the array area. Assigns color WHITE to
				all points in array. 
********************************************************************/
Board::Board(int r, int c)
{
	setRow(r);
	setCol(c);
	area = (Color**) malloc(sizeof(*area) * row);
	for (int i = 0; i < row; i++)
		area[i] = (Color*) malloc(sizeof(*area[i]) * col);
		
	for (int a = 0; a < row; a++)
		for (int b = 0; b < col; b++)
			area[a][b] = WHITE;
}

/********************************************************************
Description:	This method finishes initializing the data members
				for the Board and Ant objects, then starts moving the
				ant across the board until it runs out of steps.
********************************************************************/
void Board::run(Ant* a, int s)
{	
	langton = a;
	langton->setSteps(s);
	changeColor(langton->getRow(), langton->getCol());
	printBoard();
	while (langton->getSteps() > 0)
	{
		langton->moveAnt();
		printBoard();
		langton->setSteps(langton->getSteps() - 1);
	}
}

/********************************************************************
Description:	This method changes the color of the location of the
				box being referenced. 
********************************************************************/
void Board::changeColor(int r, int c)
{
	switch (area[r][c])
	{
		case WHITE: area[r][c] = ANT_WHITE;
			break;
		case BLACK: area[r][c] = ANT_BLACK;
			break;
		case ANT_WHITE: area[r][c] = BLACK;
			break;
		case ANT_BLACK: area[r][c] = WHITE;
			break;
	}
}

Color Board::getColor(int r, int c)
{
	return area[r][c];
}

void Board::setRow(int r)
{
	row = r;
}

void Board::setCol(int c)
{
	col = c;
}

int Board::getCol()
{
	return col;
}

int Board::getRow()
{
	return row;
}

/********************************************************************
Description:	This method prints the board with a border to help
				show where the ant is at all times.
********************************************************************/
void Board::printBoard()
{
	cout << '+';
	for (int i = 0; i < col; i++)
		cout << '-';
	cout << '+' << endl;
	for (int r = 0; r < row; r++)
	{
		cout << '|';
		for (int c = 0; c < col; c++)
			switch (area[r][c])
			{
				case BLACK: cout << '#';
					break;
				case WHITE: cout << ' ';
					break;
				case ANT_BLACK:
				case ANT_WHITE: cout << '*';
					break;
			}
		cout << '|' << endl;
	}
	cout << '+';
	for (int i = 0; i < col; i++)
		cout << '-';
	cout << '+' << endl << endl;
}