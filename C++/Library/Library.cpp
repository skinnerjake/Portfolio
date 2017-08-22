/*****************************************************
Name:			Jacob Skinner

Date:			8/7/16

Description:	This file contains the function definitions for class Library
*****************************************************/

#include <string>
#include <vector>
#include "Book.hpp"
#include "Patron.hpp"
#include "Library.hpp"

/*******************************************
Description: Constructor that sets the currentDate member to 0
*******************************************/
Library::Library()
{
	currentDate = 0;
}

/*******************************************
Description: Appends a pointer to Book to the vector holdings
*******************************************/
void Library::addBook(Book *newBook)
{
	holdings.push_back(newBook);
}

/*******************************************
Description: Appends a pointer to Patron to vector members
*******************************************/
void Library::addPatron(Patron *newPatron)
{
	members.push_back(newPatron);
}

/*******************************************
Description: Checks a book out to a patron if there are no errors; returns a string

if the specified Book is not in the Library, 
	return "book not found"
else if the specified Patron is not in the Library, 
	return "patron not found"
else if the specified Book is already checked out, 
	return "book already checked out"
else if the specified Book is on hold by another Patron, 
	return "book on hold by other patron"
else 
	update the Book's checkedOutBy, dateCheckedOut and Location; 
	if the Book was on hold for this Patron, 
		update requestedBy; 
	update the Patron's checkedOutBooks; 
	return "check out successful"
*******************************************/
std::string Library::checkOutBook(std::string pID, std::string bID)
{
	Book *currentBook = getBook(bID);
	Patron *currentPatron = getPatron(pID);
	if (currentBook == NULL)
		return "Book not found.";
	
	else if (currentPatron == NULL)
		return "Patron not found.";
	
	else if (currentBook->getLocation() == CHECKED_OUT)
		return "Book is checked out.";
	
	else if (currentBook->getLocation() == ON_HOLD_SHELF)
		return "Book is on hold.";
		
	else
	{
		currentBook->setCheckedOutBy(currentPatron);
		currentBook->setDateCheckedOut(currentDate);
		currentBook->setLocation(CHECKED_OUT);
		if (currentPatron == currentBook->getRequestedBy())
			currentBook->setRequestedBy(NULL);
		currentPatron->addBook(currentBook);
		return "Check out successful";
	}
}

/*******************************************
Description: Returns the book to the library; returns a string

if the specified Book is not in the Library, 
	return "book not found"
else if the Book is not checked out, 
	return "book already in library"
else
	update the Patron's checkedOutBooks; 
	update the Book's location depending on whether another Patron has requested it; 
	update the Book's checkedOutBy; 
	return "return successful"
*******************************************/
std::string Library::returnBook(std::string bID)
{
	Book *currentBook = getBook(bID);
	
	if (currentBook == NULL)
		return "Book not found.";
	else if (currentBook->getLocation() != CHECKED_OUT)
		return "Book is already in Library.";
	else
	{
		Patron *currentPatron = currentBook->getCheckedOutBy();
		currentPatron->removeBook(currentBook);
		if (currentBook->getRequestedBy() != NULL)
			currentBook->setLocation(ON_HOLD_SHELF);
		else 
			currentBook->setLocation(ON_SHELF);
		currentBook->setCheckedOutBy(NULL);
		return "Return successful.";
	}
}

/*******************************************
Description: A patron requests a book; returns a string

if the specified Book is not in the Library, 
	return "book not found"
else if the specified Patron is not in the Library, 
	return "patron not found"
else if the specified Book is already requested, 
	return "book already on hold"
else
	update the Book's requestedBy; 
	if the Book is on the shelf, 
		update its location to on hold; 
	return "request successful"
*******************************************/
std::string Library::requestBook(std::string pID, std::string bID)
{
	Patron *currentPatron = getPatron(pID);
	Book *currentBook = getBook(bID);
	
	if (currentBook == NULL)
		return "Book not found."; 
		
	else if (currentPatron == NULL)
		return "Patron not found.";
		
	else if (currentBook->getRequestedBy() != NULL)
		return "Book already on hold";
		
	else
	{
		currentBook->setRequestedBy(currentPatron);
		if (currentBook->getLocation() == ON_SHELF)
			currentBook->setLocation(ON_HOLD_SHELF);
		return "Request successful";
	}
}

/*******************************************
Description: Amends the fines accrued for late fees

takes as a parameter the amount that is being paid (not the negative of that amount)

if the specified Patron is not in the Library, 
	return "patron not found"
else
	use amendFine to update the Patron's fine; 
	return "payment successful"
*******************************************/
std::string Library::payFine(std::string pID, double payment)
{
	Patron *currentPatron = getPatron(pID);
	if (currentPatron == NULL)
		return "Patron not found.";
	currentPatron->amendFine(-payment);
	return "Payment successful.";
}

/*******************************************
Description: changes the current date by 1 and gives new fees for being late

increment current date; 
increase each Patron's fines by 10 cents for each overdue Book they have checked out (using amendFine)
If a book is checked out on day 0, then on day 1, the patron has had it for 1 day.  On day 21, the patron has had it for 21 days, so it is still not overdue.  On day 22, the book is overdue and fines will be charged.
*******************************************/
void Library::incrementCurrentDate()
{
	currentDate += 1;
	
	for (int p = 0; p < members.size(); p++)
	{
		Patron *currentPatron = members.at(p);
		
		for (int b = 0; b < (currentPatron->getCheckedOutBooks()).size(); b++)
		{
			Book *currentBook = (currentPatron->getCheckedOutBooks()).at(b);
			if ((currentDate - currentBook->getDateCheckedOut()) > currentBook->getCheckOutLength())
				currentPatron->amendFine(0.10);
		}
	}
}

/*******************************************
Description:  returns a pointer to the Patron corresponding to the ID parameter, or NULL if no such Patron is a member
*******************************************/
Patron* Library::getPatron(std::string pID)
{
	for (int index = 0; index < members.size(); index++)
	{
		if (members.at(index)->getIdNum() == pID)
			return members.at(index);
	}
	return NULL;
}

/*******************************************
Description: returns a pointer to the Book corresponding to the ID parameter, or NULL if no such Book is in the holdings
*******************************************/
Book* Library::getBook(std::string bID)
{
	for (int index = 0; index < holdings.size(); index++)
	{
		if (holdings.at(index)->getIdCode() == bID)
			return holdings.at(index);
	}
	return NULL;
}