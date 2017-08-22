/***************************************************************************************
Name: Jake Skinner
Date: 12/6/16
Desc: This file contains the declaration for class Ledge
***************************************************************************************/

#ifndef LEDGE_HPP
#define LEDGE_HPP

#include "Space.hpp"
#include "Board.hpp"

class Ledge: public Space
{
	public:
		Ledge(int, int, Board*);
		~Ledge() {}
		void move();
		void print();
};

#endif