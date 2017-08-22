/*************************************************************************
Name: Jake Skinner
Date: 10/31/16
Desc: This is the class declaration of Ant, a subclass of Critter
*************************************************************************/

#ifndef ANT_HPP
#define ANT_HPP

#include "Critter.hpp"
#include "World.hpp"

class Ant : public Critter
{
	public:
		Ant(int, int, int, World*);
		~Ant() {}
		void move(Direction);
		void breed(Direction);
		bool starve() {return false;}
};

#endif