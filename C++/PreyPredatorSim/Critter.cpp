/*************************************************************************
Name: Jake Skinner
Date: 10/31/16
Desc: This is the class definition of Critter
*************************************************************************/

#include "Critter.hpp"

/*************************************************************************
Desc: Constructor for Critter
*************************************************************************/
Critter::Critter(int y, int x, int b, World *w)
{
	row = y;
	col = x;
	birthday = b;
	space = w;
	move_state = WAITING;
}