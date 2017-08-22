/*************************************************************************
Name: Jake Skinner
Date: 10/31/16
Desc: This is the class declaration of Critter
*************************************************************************/

#ifndef CRITTER_HPP
#define CRITTER_HPP

#include <string>
#include "World.hpp"

enum State {WAITING, MOVED};
enum Direction {UP, RIGHT, DOWN, LEFT};

class World;

class Critter
{
	protected:
		State move_state;
		int row, col, birthday;
		World *space;
		std::string name;
	public:
		Critter(int, int, int, World*);
		virtual ~Critter() {}
		std::string getName() {return name;}
		State getMoveState() {return move_state;}
		void setMoveState(State s) {move_state = s;}
		int getBirthday() {return birthday;}
		
		//Virtual functions
		virtual void move(Direction) = 0;
		virtual void breed(Direction) = 0;
		virtual bool starve() {return false;}
};
#endif