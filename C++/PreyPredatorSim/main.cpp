/*************************************************************************
Name: Jake Skinner
Date: 10/31/16
Desc: This is the main file for the 2D prey/predator simulation.
*************************************************************************/

#include "World.hpp"
#include "Critter.hpp"
#include "Doodlebug.hpp"
#include "Ant.hpp"
#include "getInt.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	World *w;
	cout << "This is a 2D predator-prey simulation." << endl << endl
		<< "*** EXTRA CREDIT ***" << endl << endl;
	int choice = 0;
	do {cout << "Would you like to input the size of the grid?" << endl
			<< "1. Yes" << endl
			<< "2. No (default is 20x20)" << endl;
		getInt(choice);
		if ((choice != 1) and (choice != 2))
			cout << "Please input 1 or 2" << endl;
		else if (choice == 1)
		{
			int x,
				y,
				ant,
				doodlebug,
				turns;
			cout << "Enter the width" << endl;
			do {getInt(x);
				if (x < 1)
					cout << "Enter a number greater than 0" << endl;
			} while (x < 1);
			cout << "Enter the height" << endl;
			do {getInt(y);
				if (y < 1)
					cout << "Enter a number greater than 0" << endl;
			} while (y < 1);
			cout << "Enter the number of prey (maximum = " << x*y << ")"<< endl;
			do {getInt(ant);
				if (ant > (x*y))
					cout << "Enter a number between 0 and " << x*y << endl;
			} while ((ant < 0) or (ant > (x * y)));
			cout << "Enter the number of predators (maximum = " << x * y - ant << ")" << endl;
			do {getInt(doodlebug);
				if (doodlebug > (x * y - ant))
					cout << "Enter a number between 0 and " << x * y - ant << endl;
			} while ((doodlebug < 0) or (doodlebug > x * y - ant));
			cout << "Enter the number of turns" << endl;
			do {getInt(turns);
				if (turns < 1)
					cout << "Enter a number greater than 0" << endl;
			} while (turns < 1);
			w = new World(y, x, ant, doodlebug, turns);
		}
		else if (choice == 2)
		{
			int turns;
			cout << "Enter the number of turns" << endl;
			do {getInt(turns);
				if (turns < 1)
					cout << "Enter a number greater than 0" << endl;
			} while (turns < 1);
			w = new World(turns);
		}
	} while ((choice != 1) and (choice != 2));
	w->run();
	delete w;
	return 0;
}