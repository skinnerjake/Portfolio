/********************************************************************************
Name:			Jake Skinner

Date:			7/30/16

Description:	This file contains the class declaration for class TicTacToe
*********************************************************************************/

// include guards
#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

// include class Board
#include "Board.hpp"

// Class decaration of TicTacToe
class TicTacToe
{
	private:
		// private data members
		Board ticTacToeBoard;
		char turn;
	
	public:
		// Constructor; takes character argument for first turn
		TicTacToe(char);

		// Function loops through tic tac toe until game is finished
		void play();
};
#endif