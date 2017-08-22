/**********************************************************************
Name: Jake Skinner
Date: 10/23/16
Desc: This is the class definition for Item
**********************************************************************/

#include "Item.hpp" 
#include <string>
using std::string;

/**********************************************************************
Desc: Default constructor
**********************************************************************/
Item::Item()
{
	name = "";
	quantity = 0;
	price = 0;
}

/**********************************************************************
Desc: Constructor
**********************************************************************/
Item::Item(string n, Unit a, int q, double p)
{
	name = n;
	amount = a;
	quantity = q;
	price = p;
}

/**********************************************************************
Desc: Operator overload for +=
**********************************************************************/
void operator+= (Item &a, const int &b)
{
	int temp = a.getQuantity();
	a.setQuantity(temp + b);
}

/**********************************************************************
Desc: Operator overload for ==
**********************************************************************/
bool operator== (Item a, string b)
{
	return (a.getName() == b);
}