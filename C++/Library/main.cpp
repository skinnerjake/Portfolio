#include <iostream>
#include <string>
#include "Library.hpp"
#include "Patron.hpp"
#include "Book.hpp"
using namespace std;

int main()
{
	Library myLibrary;
	Book book1("123", "Ancillary Justice", "Ann Leckie"),
		book2("456", "Leviathan Wakes", "James S A Corey"),
		book3("789", "Dune", "Frank Herbert");
	Patron patron1("12345", "Jacob Skinner"),
		patron2("67890", "Erin Lawrenz");
		
	Book *b1 = &book1;
	Book *b2 = &book2;
	Book *b3 = &book3;
		
	Patron *p1 = &patron1;
	Patron *p2 = &patron2;
		
	myLibrary.addPatron(p1);
	myLibrary.addPatron(p2);
	myLibrary.addBook(b1);
	myLibrary.addBook(b2);
	myLibrary.addBook(b3);

	cout << "Erin checking out Ancillary Justice." << endl;
	cout << myLibrary.checkOutBook("67890", "123");
	cout << endl << "Jacob checking out Leviathan Wakes." << endl;
	cout << myLibrary.checkOutBook("12345", "456");
	cout << endl << "Jacob checking out Ancillary Justice." << endl;
	cout << myLibrary.checkOutBook("12345", "123");
	cout << endl << "Unknown user checking out Dune" << endl;
	cout << myLibrary.checkOutBook("45678", "789");
	cout << endl << "Erin checking out unknown book." << endl;	
	cout << myLibrary.checkOutBook("67890", "999");
	
	cout << endl << "Jacob requesting Ancillary Justice." << endl;
	cout << myLibrary.requestBook("12345", "123");
	cout << endl << "Erin returning Ancillary Justice." << endl;
	cout << myLibrary.returnBook("123");
	cout << endl << "Erin checking out Ancillary Justice." << endl;
	cout << myLibrary.checkOutBook("67890", "123");
	
	cout << endl << "50 days passed." << endl;
	for (int a = 0; a < 50; a++)
		myLibrary.incrementCurrentDate();
	
	cout << endl << "Jake's fines are: $" << patron1.getFineAmount() << endl;
	cout << endl << "Erin's fines are: $" << p2->getFineAmount() << endl;
	
	cout << endl << "Jake is paying $1" << endl;
	cout << myLibrary.payFine("12345", 1.00);
	
	cout << endl << "Jake's fines are: $" << p1->getFineAmount() << endl;

	return 0;
}