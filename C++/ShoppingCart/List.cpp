/**********************************************************************
Name: Jake Skinner
Date: 10/23/16
Desc: This is the class definition for List
**********************************************************************/
#include "Item.hpp"
#include "List.hpp"
#include "getInt.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;

/**********************************************************************
Desc: Default constructor
**********************************************************************/
List::List()
{
	length = 0;
	max_length = 4;
	shoppingList = new Item[max_length];
}

/**********************************************************************
Desc: Adds Item to list
	If Item already exists, adds to existing Item
	If array is too short to add Item, extends the array
**********************************************************************/
void List::addItem()
{
	if (length + 1 >= max_length)
		extendList();

	string name;
	Unit amount;
	int amt, loc, quantity;
	double price;
	bool inList = false;
	cout << "Enter the name of the item: " << endl;
	cin >> name;
	for (int i = 0; i < length; i++)
		if (shoppingList[i] == name)
		{
			inList = true;
			loc = i;
			break;
		}
	if (inList == false)
	{
		do {
			cout << "Choose the unit: " << endl
				<< "1. can" << endl
				<< "2. box" << endl
				<< "3. pound" << endl
				<< "4. ounce" << endl;
				
			getInt(amt);
			
			if ((amt < 1) or (amt > 4))
				cout << "Please choose an integer 1 to 4." << endl;
			
			else if (amt == 1)
				amount = can;
			else if (amt == 2)
				amount = box;
			else if (amt == 3)
				amount = pound;
			else if (amt == 4)
				amount = ounce;
		} while ((amt < 1) or (amt > 4));
		cout << "Enter the quantity: " << endl;
		getInt(quantity);
		cout << "Enter the price of the item: " << endl;
		cin >> price;
		Item a(name, amount, quantity, price);
		shoppingList[length] = a;
		length += 1;
	}
	else
	{
		cout << "This item is already in the cart." << endl
			<< "How many more would you like to add?" << endl;
		getInt(quantity);
		shoppingList[loc] += quantity;
	}
}

/**********************************************************************
Desc: Prints array and asks user to remove Item
**********************************************************************/
void List::removeItem()
{
	int choice;
	
	do {
		cout << "Choose one of the following to remove, or enter 0 to exit to the menu." << endl;
		printList();
		getInt(choice);

		if ((choice < 0) or (choice > length))
			cout << "Choose one of the integers on the list or 0." << endl;
		
		else if (choice == 0)
			return;
		
		else
		{
			Item *newArray = new Item[length];
			int newLoc = 0;
			for (int loc = 0; loc < length; loc++)
				if (loc != choice - 1)
				{
					newArray[newLoc] = shoppingList[loc];
					newLoc++;
				}
			for (int a = 0; a < length; a++)
				shoppingList[a] = newArray[a];
			length -= 1;
			delete [] newArray;
		}
	} while ((choice < 1) or (choice > length));
	
}

/**********************************************************************
Desc: Prints the list array
**********************************************************************/
void List::printList()
{
	cout << endl;
	for (int a = 0; a < length; a++)
	{
		string amt;
		switch (shoppingList[a].getAmount())
		{
			case can: 
				amt = "can";
				break;
			case box: 
				amt = "box";
				break;
			case pound: 
				amt = "pound";
				break;
			case ounce:
				amt = "ounce";
				break;
		}
		cout << a+1 << ". " << shoppingList[a].getQuantity() << " "
			<< shoppingList[a].getName() << " @ $"
			<< shoppingList[a].getPrice() << " / " << amt << endl;
	}
	cout << endl;
}

/**********************************************************************
Desc: Extends the array by doubling its size
**********************************************************************/
void List::extendList()
{
	max_length *= 2;
	Item *tempArray = new Item[max_length];
	for (int i = 0; i < length; i++)
		tempArray[i] = shoppingList[i];
	delete [] shoppingList;
	shoppingList = new Item[max_length];
	for (int i = 0; i < length; i++)
		shoppingList[i] = tempArray[i];
	delete [] tempArray;
}

/**********************************************************************
Desc: Accumulates total for all items, prints array, deletes array
**********************************************************************/
void List::checkout()
{
	double total = 0;
	for (int i = 0; i < length; i++)
		total += ((shoppingList[i]).getQuantity() * (shoppingList[i]).getPrice());
	printList();
	delete [] shoppingList;
	cout << "Total: $" << total << endl
		<< "Have a nice day!" << endl;
}
