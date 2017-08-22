/*********************************************************************
Name: 			Jacob Skinner
Date:			10/5/16
Description:	This file contains the declarations for data members 
				and methods of class Ant.
*********************************************************************/

#ifndef ANT_HPP
#define ANT_HPP

#include "Board.hpp"

enum Direction {UP, DOWN, LEFT, RIGHT}; // enumerated data type for direction of ant
class Board; // declare class Board so Ant can reference it as a data member

class Ant
{
	private:
		Direction facing; 
		int row,
			col,
			steps;
		Board *area; // pointer to Board object
	public:
		Ant(int, int, Board*); // constructor
		void setRow(int);
		void setCol(int);
		int getRow();
		int getCol();
		void setSteps(int);
		int getSteps();
		void moveAnt(); // move the Ant
		void turnAnt(); // turn the Ant
		void wrapBoard(); // keeps the Ant from running out of bounds
};

#endif