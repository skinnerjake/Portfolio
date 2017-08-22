/*********************************************************************
Name: 			Jacob Skinner
Date:			10/5/16
Description:	This file contains the definitions for the function
				Menu. It takes five 'int' types by reference, and 
				utilizes loops to assign values. It makes use of the
				input_integer function to validate input.
*********************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "input_integer.hpp"

using std::cin;
using std::cout;
using std::endl;

void menu(int &row, int &col, int &turns, int &ant_x, int &ant_y)
{
	int choice = 0;
	cout << "This is a simulation of Langton's Ant." << endl
		<< "Input the number of rows you would like to use: ";
	
	
	do {input_integer(row);
		if (row <= 0)
			cout << "Please input an integer greater than 0: ";
	} while (row <= 0);
	
	
	cout << "Input the number of columns you would like to use: ";
	do {input_integer(col);
		if (col <= 0)
			cout << "Please input an integer greater than 0: ";
	} while (col <= 0);


	cout << "Input the number of turns you would like. " << endl
		<< "It is recommended that you input " << row * col << " turns." << endl;
	do {input_integer(turns);
		if (turns < 0)
			cout << "Please input an integer greater than or equal to zero: ";
	} while (turns < 0);
	
	
	cout << "Would you like to input the starting spot of the ant?" << endl
		<< "1. Yes" << endl
		<< "2. No" << endl;
	do {input_integer(choice);
		if ((choice < 1) or (choice > 2))
			cout << "Please input either 1 or 2: ";
	} while ((choice != 1) and (choice != 2));
	
	
	if (choice == 1)
	{	
		cout << "Input the x/column coordinate: ";
		do {input_integer(ant_x);
			if ((ant_x < 0) or (ant_x >= col))
				cout << "Input a column value between 0 and " << (col - 1) << ": ";
		} while ((ant_x < 0) or (ant_x >= col));
		
		
		cout << "Input the y/row coordinate: ";
		do {
			input_integer(ant_y);
			if ((ant_y < 0) or (ant_y >= row))
				cout << "Input a row value between 0 and " << (row - 1) << ": ";
		} while ((ant_y < 0) or (ant_y >= col));
	}
	
	
	else if (choice == 2)
	{
		srand(time(NULL));
		ant_x = rand() % col;
		ant_y = rand() % row;
	}
}