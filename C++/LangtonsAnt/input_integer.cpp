/*********************************************************************
Name: 			Jacob Skinner
Date:			10/5/16
Description:	This file contains the function definition for the 
				input_integer function. It takes an integer by 
				reference as an argument, then loops until the user 
				inputs a valid integer. It returns nothing.
*********************************************************************/

#include <iostream>
using std::cin;
using std::cout;

void input_integer(int &num)
{
	cin >> num;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Please input an integer: ";
		cin >> num;
	}
}
