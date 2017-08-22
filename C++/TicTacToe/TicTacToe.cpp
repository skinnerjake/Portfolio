/********************************************************************************
Name:			Jake Skinner

Date:			7/30/16

Description:	This file contains the function definitions for class TicTacToe
*********************************************************************************/

// Include classes Board and TicTacToe
#include "Board.hpp"
#include "TicTacToe.hpp"

#include <iostream>		// output and input
#include <cctype>		// toupper
using namespace std;

/**********************************************************
** Definition: Constructor for TicTacToe; takes a character
** 		argument then assigns value to turn
**********************************************************/
TicTacToe::TicTacToe(char firstTurn)
{
	turn = toupper(firstTurn);
}

/**********************************************************
** Definition: Function runs the game of tic tac toe:
**		1. Prints the board
**		2. Loops through turns until game is resolved
**		3. Provides feedback based on the resulting state
**********************************************************/
void TicTacToe::play()
{
	// Print an empty board
	ticTacToeBoard.print();
	
	// Loops until gameState is not UNFINISHED
	do {
		int xCoord,
			yCoord;
			
		// Get two integer coordinates from user
		cout << turn << ": Enter your x- and y-coordinates: " << endl << "X: ";
		cin >> xCoord;
		cout << "Y: ";
		cin >> yCoord;
		
		// Make a move
		// Return true if move recorded
		bool unoccupied = ticTacToeBoard.makeMove(xCoord, yCoord, turn);
		
		// If move was not recorded, ask for new coordinates and restart loop
		if (unoccupied == false)
		{
			cout << "The square is already occupied." << endl
				<< "Make another move." << endl;
			continue;
		}
		
		// Switch turns
		if (turn == 'X')
			turn = 'O';
		else if (turn == 'O')
			turn = 'X';
			
		// Print a new board
		ticTacToeBoard.print();
	} while (ticTacToeBoard.gameState() == UNFINISHED);
	
	// Give feedback based on gameState that broke the loop
	if (ticTacToeBoard.gameState() == DRAW)
		cout << "Draw game!" << endl;
	else if (ticTacToeBoard.gameState() == X_WON)
		cout << "X wins!" << endl;
	else if (ticTacToeBoard.gameState() == O_WON)
		cout << "O wins!" << endl;
}


/**********************************************************
** Definition: Main function for TicTacToe
**********************************************************/
int main()
{
	char firstTurn;
	system("Clear");
	cout << "To start a game, please enter either 'X' or 'O' as the first turn: ";
	cin >> firstTurn;
	TicTacToe newGame(firstTurn);
	newGame.play();

	return 0;
}