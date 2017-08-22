/**********************************************************************
Name: Jake Skinner
Date: 10/23/16
Desc: This is the class declaration for Item
**********************************************************************/
#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
using std::string;

enum Unit {can, box, pound, ounce};

class Item
{
	private:
		string name;
		Unit amount;
		int quantity;
		double price;
	public:
		Item(string, Unit, int, double);
		Item();
		string getName() {return name;}
		Unit getAmount() {return amount;}
		void setQuantity(int q) {quantity = q;}
		int getQuantity() {return quantity;}
		double getPrice() {return price;}

		friend bool operator== (Item a, string b);
		friend void operator+= (Item &a, const int &b);

};

#endif