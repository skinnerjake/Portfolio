/*****************************************************
Name:			Jacob Skinner

Date:			8/7/16

Description:	This file contains the function definitions for class Book
*****************************************************/

#include "Book.hpp"
#include "Patron.hpp"
#include <string>

/*******************************************
Description: Constructor that sets the ID code, title, and author of a book
*******************************************/
Book::Book(std::string idc, std::string t, std::string a)
{
	idCode = idc;
	title = t;
	author = a;
}

int Book::getCheckOutLength()
{
	return CHECK_OUT_LENGTH;
}

std::string Book::getIdCode()
{
	return idCode;
}

std::string Book::getTitle()
{
	return title;
}

std::string Book::getAuthor()
{
	return author;
}

Locale Book::getLocation()
{
	return location;
}

void Book::setLocation(Locale place)
{
	location = place;
}

Patron* Book::getCheckedOutBy()
{
	return checkedOutBy;
}

void Book::setCheckedOutBy(Patron *p)
{
	checkedOutBy = p;
}

Patron* Book::getRequestedBy()
{
	return requestedBy;
}

void Book::setRequestedBy(Patron *p)
{
	requestedBy = p;
}

int Book::getDateCheckedOut()
{
	return dateCheckedOut;
}

void Book::setDateCheckedOut(int date)
{
	dateCheckedOut = date;
}