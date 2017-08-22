/***************************************************************************************
Name: Jake Skinner
Date: 12/6/16
Desc: This file contains the member definitions for the class Board
***************************************************************************************/

#include "Board.hpp"
#include "Space.hpp"
#include "Tile.hpp"
#include "Edge.hpp"
#include "Ledge.hpp"
#include "Player.hpp"
#include <cstdlib>
#include <string>
#include <iostream>

// Board constructor
Board::Board(std::string n)
{
	key = n;
	int size = n.length();
	maxX = (size * 2) + 1;
	maxY = (size * 2) + 3;
	area = new Space**[maxY];
	for (int y = 0; y < maxY; y++)
		area[y] = new Space*[maxX];
	for (int y = 0; y < maxY; y++)
		for (int x = 0; x < maxX; x++)
		{
			if (y == 0 || y == maxY-1)
				area[y][x] = new Ledge(y, x, this);
			else if (y%2 == 1)
				area[y][x] = new Edge(y, x, this);
			else if (x%2 == 0)
				area[y][x] = new Edge(y, x, this);
			else if (y%2 == 0 && x%2 == 1)
				area[y][x] = new Tile(y, x, this);
		}
	int x = (rand() % size) * 2 + 1;
	int i = 0;
	for (int y = maxY - 3; y > 0; y -= 2)
	{
		area[y][x]->setLetter(toupper(key.at(i)));
		if (x == 1)
			x += (rand() % 2) * 2;
		else if (x == maxX - 2)
			x -= (rand() % 2) * 2;
		else
			x += (rand() % 3 - 1) * 2;
		i++;
	}
}

// Function prints out letter for each space in the board
void Board::print()
{
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (area[y][x] != NULL)
				area[y][x]->print();
			else
				std::cout << '#';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Board::~Board()
{
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
			if (area[y][x] != NULL)
				delete area[y][x];
		delete [] area[y];
	}
	delete [] area;
}