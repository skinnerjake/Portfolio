/***************************************************************************************
Name: Jake Skinner
Date: 12/6/16
Desc: This file contains the member definitions for the class Edge
***************************************************************************************/

#include "Space.hpp"
#include "Edge.hpp"
#include <iostream>
#include <cstdlib>

// Constructor for Edge
Edge::Edge(int y_, int x_, Board *a) : Space(y_, x_, a)
{
	left = NULL;
	right = NULL;
	center = NULL;
	if (y_ == 0 || y_ == area->getMaxY()-1)
		letter = ' ';
	else if (y_ == 1 || y_ == area->getMaxY()-2)
		letter = '=';
	else if (y_ % 2 == 0 && x_ % 2 == 0)
		letter = '|';
	else if (y_ % 2 == 1 && x_ % 2 == 0)
		letter = '+';
	else if (y_ % 2 == 1 && x_ % 2 == 1)
		letter = '-';
	else
		std::cout << "This should not print" << std::endl;
}

// Prints out letter
void Edge::print()
{
	// if not fogged
	std::cout << letter;
}