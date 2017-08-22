/***************************************************************************************
Name: Jake Skinner
Date: 12/6/16
Desc: This file contains the member definitions for the class Player
***************************************************************************************/

#include <iterator>
#include "Player.hpp"
#include "Space.hpp"
#include <iostream>
#include <cstdlib>
#include "getInt.hpp"
#include <algorithm>

Player::Player(int y_, int x_, Board *a)
{
	lives = 0;
	y = y_;
	x = x_;
	area = a;
	location = area->getSpace(y, x);
	location->setOccupancy(FILLED);
}

void Player::move()
{
	std::string Compass[] = 
		{
		// top row + middle
			// none = 0
			"\t       \n\t        \n",
			// left = 1
			"\t1      \n\t \\     \n",
			// up = 2
			"\t   2   \n\t   |    \n",
			// right = 3
			"\t      3\n\t     /  \n",
			// left up = 4
			"\t1  2   \n\t \\ |   \n",
			// left right = 5
			"\t1     3\n\t \\   / \n",
			// up right = 6
			"\t   2  3\n\t   | /  \n",
			// left up right = 7
			"\t1  2  3\n\t \\ | / \n",
			
		// bottom row:
			// neither = 8
			"\t   @   \n",
			// left = 9
			"\t4<-@   \n",
			// right = 10
			"\t   @->5\n",
			// both = 11
			"\t4<-@->5\n"
		};

	int choice = 0;
	int options[5];
	int index = 0;
	
	std::cout << "Word: " << name << std::endl
		<< "-------Compass:-------" << std::endl << std::endl;
	if (location->getLeft() == NULL && location->getRight() == NULL)
	{
		std::cout << Compass[2];
		options[index] = 2;
		index++;
	}
	else if (location->getRight() == NULL)
	{
		std::cout << Compass[4];
		options[index] = 1;
		index++;
		options[index] = 2;
		index++;
	}
	else if (location->getLeft() == NULL)
	{
		std::cout << Compass[6];
		options[index] = 2;
		index++;
		options[index] = 3;
		index++;
	}
	else
	{
		std::cout << Compass[7];
		options[index] = 1;
		index++;
		options[index] = 2;
		index++;
		options[index] = 3;
		index++;
	}

	if (y == area->getMaxY() - 1)
	{
		if (x == 1 && x == area->getMaxX() - 2)
			std::cout << Compass[8];
		else if (x == 1)
		{
			std::cout << Compass[10];
			options[index] = 5;
			index++;
		}
		else if (x == area->getMaxX() - 2)
		{
			std::cout << Compass[9];
			options[index] = 4;
			index++;
		}
		else
		{
			std::cout << Compass[11];
			options[index] = 4;
			index++;
			options[index] = 5;
			index++;
		}
	}
	else
		std::cout << Compass[8];

	std::cout << "Player 2: Enter a choice from the comapss:" << std::endl;
	
	bool found = false;
	do {
		getInt(choice);
		int* f = std::find(options, options + index, choice);
		if (f != options + index)
			found = true;
	} while (found == false);

	if (choice == 1)
	{
		location->setOccupancy(VACANT);
		(area->getSpace(y-1, x-1))->setLetter('\\');
		y -= 2;
		x -= 2;
		location = location->getLeft();
		location->setOccupancy(FILLED);
		addLetter(location->getLetter());
	}
	else if (choice == 2)
	{
		location->setOccupancy(VACANT);
		(area->getSpace(y-1, x))->setLetter('|');
		y -= 2;
		location = location->getCenter();
		location->setOccupancy(FILLED);
		addLetter(location->getLetter());
	}
	else if (choice == 3)
	{
		location->setOccupancy(VACANT);
		(area->getSpace(y-1, x+1))->setLetter('/');
		y -= 2;
		x += 2;
		location = location->getRight();
		location->setOccupancy(FILLED);
		addLetter(location->getLetter());
	}
	else if (choice == 4)
	{
		location->setOccupancy(VACANT);
		x -= 2;
		location = area->getSpace(y, x);
		location->setOccupancy(FILLED);
	}
	else if (choice == 5)
	{
		location->setOccupancy(VACANT);
		x += 2;
		location = area->getSpace(y, x);
		location->setOccupancy(FILLED);
	}
	else
		std::cout << "This should not print" << std::endl;
}

void Player::die()
{
	lives++;
	name = "";
	std::cout << "You died!\nLives: " << lives << std::endl;
	location->setLetter('#');
	location->setOccupancy(VACANT);
	y = area->getMaxY() - 1;
	x = (rand() % area->getMaxX());
	if (x % 2 == 0)
		x++;
	location = area->getSpace(y, x);
	location->setOccupancy(FILLED);
}

Player::~Player()
{
	
}