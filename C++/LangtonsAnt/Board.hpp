/*********************************************************************
Name: 			Jacob Skinner
Date:			10/5/16
Description:	This file contains the declarations for methods and
				data members of class Ant.
*********************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Ant.hpp"

enum Color {WHITE, BLACK, ANT_WHITE, ANT_BLACK}; // enumerated data type for board color

class Ant; // declare Ant so an Ant object can be a data member

class Board
{
	private:
		Color **area;
		int row,
			col;
		Ant *langton;
	public:
		Board(int, int); // constructor
		void run(Ant*, int); // method runs the output
		void changeColor(int, int); // changes color of a particular input
		Color getColor(int, int); 
		void setRow(int);
		void setCol(int);
		int getCol();
		int getRow();
		void printBoard(); // outputs the board
};

#endif