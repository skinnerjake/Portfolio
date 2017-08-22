/***************************************************************************************
Name: Jake Skinner
Date: 12/6/16
Desc: This file contains the declaration for class Edge
***************************************************************************************/

#ifndef EDGE_HPP
#define EDGE_HPP

#include "Space.hpp"
#include "Board.hpp"

class Edge : public Space
{
	public:
		Edge(int, int, Board*);
		~Edge() {};
		void move() {};
		void print();
};

#endif