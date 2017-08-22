/********************************************************************************
Name:			Jake Skinner

Date:			7/30/16

Description:	This file contains the function definitions for class Board
*********************************************************************************/

#include "Board.hpp"
#include <iostream>
using namespace std;

/**********************************************************
** Definition: Default constructor for class Board;
** 		assigns each value of 2D array as 0;
** 		assigns currentState as UNFINISHED
**********************************************************/
Board::Board()
{
	for (int xCoord = 0; xCoord < 3; xCoord++)
	{
		for (int yCoord = 0; yCoord < 3; yCoord++)
			boardArray[xCoord][yCoord] = 0;
	}
	currentState = UNFINISHED;
}

/**********************************************************
** Definition: Helper function for gameState;
** 		checks if any player won vertically
**********************************************************/
void Board::winVertical()
{
	for (int xCoord = 0; xCoord < 3; xCoord++)		
		checkWin(boardArray[xCoord][0], boardArray[xCoord][1], boardArray[xCoord][2]);
}


/**********************************************************
** Definition: Helper function for gameState;
**		checks if any player won horizontally
**********************************************************/
void Board::winHorizontal()
{
	for (int yCoord = 0; yCoord < 3; yCoord++)		
		checkWin(boardArray[0][yCoord], boardArray[1][yCoord], boardArray[2][yCoord]);
}


/**********************************************************
** Definition: Helper function for gameState;
**		checks if any player won on the right diagonal
**********************************************************/
void Board::winDiagonalRight()
{
	checkWin(boardArray[0][2], boardArray[1][1], boardArray[2][0]);
}


/**********************************************************
** Definition: Helper function for gameState;
** 		checks if any player won on the left diagonal
**********************************************************/
void Board::winDiagonalLeft()
{
	checkWin(boardArray[0][0], boardArray[1][1], boardArray[2][2]);
}


/**********************************************************
** Definition: Helper function for gameState;
** 		checks if the game is a finished and a draw
**********************************************************/
void Board::drawGame()
{
	bool draw = true;
	for (int xCoord = 0; xCoord < 3; xCoord++)
	{
		for (int yCoord = 0; yCoord < 3; yCoord++)
		{
			if (boardArray[xCoord][yCoord] == 0)
				draw = false;
		}
	}
	if ((draw == true) and (currentState == UNFINISHED))
		currentState = DRAW;
}


/**********************************************************
** Definition: Helper function for gameState;
** 		takes 3 characters;
**		if characters match, changes currentState to X_WON or O_WON
**********************************************************/
void Board::checkWin(char tic, char tac, char toe)
{
	if ((tic == 'X') and (tac == 'X') and (toe == 'X'))
		currentState = X_WON;
	else if ((tic == 'O') and (tac == 'O') and (toe == 'O'))
		currentState = O_WON;
}


/**********************************************************
** Definition: Function takes 2 coordinate integers and a character (x or o);
** 		if coordinate location is empty, record character and return true;
**		if coordinate location is full, return false
**********************************************************/
bool Board::makeMove(int xCoord, int yCoord, char turn)
{
	if (boardArray[xCoord-1][yCoord-1] == 0)
	{
		boardArray[xCoord-1][yCoord-1] = turn;
		return true;
	}
	else
		return false;
}


/**********************************************************
** Definition: Function returns enumerated type of the
**		state of the game (UNFINISHED, X_WON, O_WON, DRAW);
**		uses helper functions to change currentState if
**		necessary, then returns it.
**********************************************************/
state Board::gameState()
{
	winVertical();
	winHorizontal();
	winDiagonalLeft();
	winDiagonalRight();
	drawGame();
	return currentState;
}

/**********************************************************
** Definition: function clears the screen then outputs the
**		most recent board based on boardArray
**********************************************************/
void Board::print()
{
	system("clear");
	cout << "  1 2 3 " << endl;
	for (int yCoord = 0; yCoord < 3; yCoord++)
	{
		cout << (yCoord + 1) << " ";
		for (int xCoord = 0; xCoord < 3; xCoord++)
		{
			if (boardArray[xCoord][yCoord] == 0)
				cout << "_ ";
			else
				cout << boardArray[xCoord][yCoord] << " ";
		}
		cout << endl;
	}
}