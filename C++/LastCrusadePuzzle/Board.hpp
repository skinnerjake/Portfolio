/***************************************************************************************
Name: Jake Skinner
Date: 12/6/16
Desc: This file contains the declaration for class Board
***************************************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Space.hpp"
#include "Player.hpp"
#include <string>

// Forward declarations of Space and Player
class Space;
class Player;

class Board
{
	private:
		int maxX,
			maxY;
		Space ***area;
		std::string key;
	public:
		Board(std::string);
		~Board();
		Space* getSpace(int y, int x) {return area[y][x];}
		int getMaxX() {return maxX;}
		int getMaxY() {return maxY;}
		void print();
};

#endif