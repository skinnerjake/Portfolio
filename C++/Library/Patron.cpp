/*****************************************************
Name:			Jacob Skinner

Date:			8/7/16

Description:	This file contains the function definitions for class Patron
*****************************************************/

#include "Patron.hpp"
#include "Book.hpp"
#include <string>
#include <vector>

/*******************************************
Description: Constructor that takes an idNum and name and initializes fineAmount to zero
*******************************************/
Patron::Patron(std::string idn, std::string n)
{
	idNum = idn;
	name = n;
	fineAmount = 0.0;
}

std::string Patron::getIdNum()
{
	return idNum;
}

std::string Patron::getName()
{
	return name;
}

std::vector<Book*> Patron::getCheckedOutBooks()
{
	return checkedOutBooks;
}

/*******************************************
Description: adds the pointer to specified Book to vector checkedOutBooks
*******************************************/
void Patron::addBook(Book* b)
{
	checkedOutBooks.push_back(b);
}

/*******************************************
Description: removes the pointer to specified Book from vector checkedOutBooks
*******************************************/
void Patron::removeBook(Book* b)
{
	for (int index = 0; index > checkedOutBooks.size(); index++)
	{
		if (checkedOutBooks.at(index) == b)
		{
			checkedOutBooks.erase(checkedOutBooks.begin()+index);
			continue;
		}
	}
}

double Patron::getFineAmount()
{
	return fineAmount;
}

/*******************************************
Description: takes a double and alters fineAmount; 
a positive argument increases the fineAmount, a negative one decreases it
*******************************************/
void Patron::amendFine(double amount)
{
	fineAmount += amount;
}