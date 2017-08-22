/*************************************************************************
Name: Jake Skinner
Date: 10/31/16
Desc: This is the class definition for World
*************************************************************************/

#include "World.hpp"
#include "Critter.hpp"
#include "Doodlebug.hpp"
#include "Ant.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <string>
using std::cout;
using std::endl;

/*************************************************************************
Desc: Constructor for World that takes one argument, turns
*************************************************************************/
World::World(int turns)
{
	srand(time(NULL));
	int num_doodlebug = 0,
		num_ant = 0;
	turns_ = turns;
	size_x_ = 20;
	size_y_ = 20;
	
	// Dynamically allocate 2D array
	grid = new Critter**[size_y_];
	for (int y = 0; y < size_y_; y++)
		grid[y] = new Critter*[size_x_];
		
	// Empty array
	for (int y = 0; y < size_y_; y++)
		for (int x = 0; x < size_x_; x++)
			grid[y][x] = NULL;

	while (num_doodlebug < 5)
	{
		int y = rand() % size_y_;
		int x = rand() % size_x_;
		if (grid[y][x] == NULL)
		{
			grid[y][x] = new Doodlebug(y,x,turns,this);
			num_doodlebug++;
		}
	}
	
	while (num_ant < 100)
	{
		int y = rand() % size_y_;
		int x = rand() % size_x_;
		if (grid[y][x] == NULL)
		{
			grid[y][x] = new Ant(y,x,turns,this);
			num_ant++;
		}
	}
}

/*************************************************************************
Desc: Constructor for World that takes 5 arguments:
		- height
		- width
		- number of prey
		- number of predators
		- turns
*************************************************************************/
World::World(int y, int x, int ant, int doodlebug, int turns)
{
	srand(time(NULL));
	int num_doodlebug = 0,
		num_ant = 0;
	turns_ = turns;
	size_x_ = x;
	size_y_ = y;
	
	// Dynamically allocate 2D array
	grid = new Critter**[size_y_];
	for (int y = 0; y < size_y_; y++)
		grid[y] = new Critter*[size_x_];
		
	// Empty array
	for (int y = 0; y < size_y_; y++)
		for (int x = 0; x < size_x_; x++)
			grid[y][x] = NULL;

	while (num_doodlebug < doodlebug)
	{
		int y = rand() % size_y_;
		int x = rand() % size_x_;
		if (grid[y][x] == NULL)
		{
			grid[y][x] = new Doodlebug(y,x,turns,this);
			num_doodlebug++;
		}
	}
	
	while (num_ant < ant)
	{
		int y = rand() % size_y_;
		int x = rand() % size_x_;
		if (grid[y][x] == NULL)
		{
			grid[y][x] = new Ant(y,x,turns,this);
			num_ant++;
		}
	}
}

/*************************************************************************
Desc: Function to see if a coordinate is within the bounds of the array.
		Takes two integers (y and x coordinates).
		Returns boolean value
*************************************************************************/
bool World::inBounds(int y, int x)
{
	if ((x >= 0) and (x < size_x_) and (y >= 0) and (y < size_y_))
		return true;
	else 
		return false;
}

/*************************************************************************
Desc: Prints the current 2D array and number of turns remaining
*************************************************************************/
void World::print()
{
	std::string top = '+' + std::string(size_x_, '-') + '+';
	cout << top << endl;
	for (int y = 0; y < size_y_; y++)
	{
		cout << '|';
		for (int x = 0; x < size_x_; x++)
		{
			if ((grid[y][x] != NULL) and (grid[y][x]->getName() == "Ant"))
				cout << "X";
			else if ((grid[y][x] != NULL) and (grid[y][x]->getName() == "Doodlebug"))
				cout << "O";
			else if (grid[y][x] == NULL)
				cout << "_";
		}
		cout << '|' << endl;
	}
	cout << top << endl;
	cout << "Turns left: " << turns_ << endl;
}

/*************************************************************************
Desc: Destructor for World. Deletes the 2D array of pointers to Critter
*************************************************************************/
World::~World()
{
	for (int y = 0; y < size_y_; y++)
	{
		for (int x = 0; x < size_x_; x++)
			if (grid[y][x] != NULL)
				delete grid[y][x];
		delete [] grid[y];
	}
	delete [] grid;
}

/*************************************************************************
Desc: Moves, starves, and breeds the Critters
*************************************************************************/
void World::executeTurn()
{
	//Moving Doodlebugs
	for (int y = 0; y < size_y_; y++)
		for (int x = 0; x < size_x_; x++)
			if ((grid[y][x] != NULL) and (grid[y][x]->getName() == "Doodlebug"))
					grid[y][x]->move(Direction(rand() % 4));

	//Moving Ants
	for (int y = 0; y < size_y_; y++)
		for (int x = 0; x < size_x_; x++)
			if ((grid[y][x] != NULL) and (grid[y][x]->getName() == "Ant"))
					grid[y][x]->move(Direction(rand() % 4));	

	//Starving Doodlebugs
	for (int y = 0; y < size_y_; y++)
		for (int x = 0; x < size_x_; x++)
			if ((grid[y][x] != NULL) and (grid[y][x]->getName() == "Doodlebug") and (grid[y][x]->starve()))
						starveDoodlebug(y, x);

	// Breed Doodlebugs
	for (int y = 0; y < size_y_; y++)
		for (int x = 0; x < size_x_; x++)
			if (grid[y][x] != NULL)
				if (grid[y][x]->getName() == "Doodlebug")
					grid[y][x]->breed(Direction(rand() % 4));
	//Breed ants
	for (int y = 0; y < size_y_; y++)
		for (int x = 0; x < size_x_; x++)
			if (grid[y][x] != NULL)
				if (grid[y][x]->getName() == "Ant")
					grid[y][x]->breed(Direction(rand() % 4));
					
	//Resetting move_state to WAITING
	for (int y = 0; y < size_y_; y++)
		for (int x = 0; x < size_x_; x++)
			if (grid[y][x] != NULL)
				grid[y][x]->setMoveState(WAITING);
}

/*************************************************************************
Desc: executes and prints the board for each turn
*************************************************************************/
void World::run()
{
	cout << endl << "START:" << endl;
	print();
	while (turns_ > 0)
	{
		executeTurn();
		turns_--;
		print();
	}
}

/*************************************************************************
Desc: Creates a new Doodlebug object at a particular coordinate
*************************************************************************/
void World::newDoodlebug(int y, int x)
{
	grid[y][x] = new Doodlebug(y, x, turns_, this);
}

/*************************************************************************
Desc: Creates a new Ant object at a particular coordinate
*************************************************************************/
void World::newAnt(int y, int x)
{
	grid[y][x] = new Ant(y, x, turns_, this);
}

/*************************************************************************
Desc: Deletes an object at a particular coordinate
*************************************************************************/
void World::starveDoodlebug(int y, int x)
{
	delete grid[y][x];
	grid[y][x] = NULL;
}