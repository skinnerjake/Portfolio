/***************************************************************************************
Name: Jake Skinner
Date: 12/6/16
Desc: This file contains the declaration for class Player
***************************************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Board.hpp"
#include "Space.hpp"
#include <string>

// class prototypes
class Space;
class Board;

class Player
{
	private:
		int x,
			y,
			lives;
		Space *location;
		Board *area;
		std::string name;
	public:
		Player(int, int, Board*);
		~Player();
		void move();
		void die();
		int getLives() {return lives;}
		Space* getLocation() {return location;}
		void addLetter(char c) {name += c;}
		std::string getName() {return name;}
};

#endif