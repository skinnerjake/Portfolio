/*********************************************************************
Name: 			Jacob Skinner
Date:			10/5/16
Description:	This is the main file for running Langton's Ant. It
				utilizes class Board, class Ant, and function Menu.
*********************************************************************/

#include "Ant.hpp"
#include "Board.hpp"
#include "menu.hpp"
#include "input_integer.hpp"

int main()
{
	int row = 0,
		col = 0,
		turns = 0,
		y = 0,
		x = 0;
	
	// initialize integers with menu function
	menu(row, col, turns, x, y);
	
	// construct board
	Board b(row, col);
	Board *pB = &b;
	
	Ant a(y, x, pB);
	Ant *pA = &a;
	
	b.run(pA, turns); //
	b.printBoard();
	
	return 0;
}