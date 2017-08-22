/***************************************************************************************
Name: Jake Skinner
Date: 12/6/16
Desc: This file contains the declaration for class Space
***************************************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include "Board.hpp"

enum Occupant {VACANT, FILLED};
class Board;

class Space
{
	protected:
		int y,
			x;
		Space *left,
			*right,
			*center;
		Board *area;
		char letter;
		Occupant opening;
	public:
		Space(int, int, Board*);
		virtual ~Space() {};
		void link();
		void setLetter(char l) {letter = l;}
		char getLetter() {return letter;}
		void setOccupancy(Occupant o) {opening = o;}
		virtual void print() {};
		Space* getLeft() {return left;}
		Space* getCenter() {return center;}
		Space* getRight() {return right;}
};

#endif