/*************************************************************************
Name: Jake Skinner
Date: 10/31/16
Desc: This is the class declaration of Doodlebug, a subclass of Critter
*************************************************************************/

#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "Critter.hpp"
#include "World.hpp"

class Doodlebug : public Critter
{
	private:
		int starveCounter;
	public:
		Doodlebug(int, int, int, World*);
		~Doodlebug() {}
		void move(Direction);
		void breed(Direction);
		bool starve();
};

#endif