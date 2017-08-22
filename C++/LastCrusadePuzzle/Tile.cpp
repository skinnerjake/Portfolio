/***************************************************************************************
Name: Jake Skinner
Date: 12/6/16
Desc: This file contains the member definitions for the class Tile
***************************************************************************************/

#include "Space.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include <iostream>
#include <cstdlib>
const char Tile::bank[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

Tile::Tile(int y_, int x_, Board* a) : Space(y_, x_, a)
{
	exposed = FOG;
	letter = bank[rand()%bankSize];
	if (x == 1 || y == 0 || y == 1)
		left = NULL;
	else
		left = area->getSpace(y-2, x-2);
	// set center
	if (y == 0 || y == 1)
		center = NULL;
	else
		center = area->getSpace(y-2, x);
	// set right
	if (x == area->getMaxX() - 2 || y == 0 || y == 1)
		right = NULL;
	else
		right = area->getSpace(y-2, x+2);
}

void Tile::print()
{
	if (opening == FILLED)
		std::cout << '@';
	else
		std::cout << letter;
}