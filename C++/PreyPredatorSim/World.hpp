/*************************************************************************
Name: Jake Skinner
Date: 10/31/16
Desc: This is the class declaration for World
*************************************************************************/

#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include "Critter.hpp"

class Critter;

class World
{
	private:
		int size_x_,
			size_y_,
			turns_;
		Critter ***grid;
	public:
		World(int);
		World(int, int, int, int, int);
		~World();
		Critter* getCritter(int y, int x) {return grid[y][x];}
		void setCritter(int y, int x, Critter* c) {grid[y][x] = c;}
		int getTurns() {return turns_;}
		void starveDoodlebug(int, int);
		void newDoodlebug(int, int);
		void newAnt(int, int);
		bool inBounds(int, int);
		void executeTurn();
		void run();
		void print();
};

#endif