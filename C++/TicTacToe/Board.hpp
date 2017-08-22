/********************************************************************************
Name:			Jake Skinner

Date:			7/30/16

Description:	This file contains the class declaration for class Board
*********************************************************************************/

// include guards
#ifndef BOARD_HPP
#define BOARD_HPP

// Universal enumerate type state
enum state {X_WON, O_WON, DRAW, UNFINISHED};

// Class declaration of Board
class Board
{
	private:
		// Private data members
		char boardArray[3][3];
		state currentState;
		
		// Private helper functions to determine gameState
		void winVertical();
		void winHorizontal();
		void winDiagonalLeft();
		void winDiagonalRight();
		void drawGame();
		void checkWin(char, char, char);
		
	public:
		// Default constructor
		Board();
		
		// Function takes two coordinates and character for turn (x or o)
		// If empty, assign character to location and return true
		// If occupied, return false
		bool makeMove(int, int, char);
		
		// Function returns current state of the game (winner, draw, unfinished)
		state gameState();
		
		// Function prints out the most recent game board
		void print();
};
#endif