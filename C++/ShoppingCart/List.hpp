/**********************************************************************
Name: Jake Skinner
Date: 10/23/16
Desc: This is the class declaration for List
**********************************************************************/
#ifndef LIST_HPP
#define LIST_HPP

#include "Item.hpp"

class Item;

class List
{
	private:
		Item *shoppingList;
		int length;
		int max_length;
	public:
		List();
		void addItem();
		void removeItem();
		void printList();
		void extendList();
		void checkout();
};

#endif