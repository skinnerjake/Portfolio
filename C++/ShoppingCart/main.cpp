/**********************************************************************
Name: Jake Skinner
Date: 10/23/16
Desc: This is the main file for Assignment2
**********************************************************************/

#include "Item.hpp"
#include "List.hpp"
#include "getInt.hpp"
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	List list;
	int choice = 0;
	cout << "Hello! Please choose one of the following:" << endl;
	do{
		cout << "1. Add item to cart" << endl
			<< "2. Remove item from cart" << endl
			<< "3. See the items in the cart" << endl
			<< "4. Checkout" << endl;
		
		getInt(choice);
		
		if ((choice < 1) or (choice > 4))
			cout << "Please input a number between 1 and 4." << endl;
			
		else if (choice == 1)
			list.addItem();
		else if (choice == 2)
			list.removeItem();
		else if (choice == 3)
			list.printList();
		else if (choice == 4)
			list.checkout();
	} while (choice != 4);
	return 0;
}