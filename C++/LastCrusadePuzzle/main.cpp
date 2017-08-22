/***************************************************************************************
Name: Jake Skinner
Date: 12/6/16
Desc: This is the main file for the Indiana Jones "Name of God" game
***************************************************************************************/

#include "Board.hpp"
#include "Player.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

int main()
{
	std::cout << std::endl << "--------------------------------------------------" << std::endl << std::endl
				<< "This is a game based on the \"Name of God\" puzzle" << std::endl
				<< "from the movie Indiana Jones and the Last Crusade." << std::endl
				<< "Player 1 will input the code to cross the board, as " << std::endl
				<< "well as a clue to help the other player solve. " << std::endl << std::endl
				<< "Example from the movie:	\ncode: IEHOVA\tclue: NAME OF GOD" << std::endl << std::endl
				<< "Player 2 will play as the character (@) trying to" << std::endl
				<< "cross the board. If the player chooses incorrectly," << std::endl
				<< "he will die and the letter in the floor will fall" << std::endl
				<< "through, causing the tile to become empty (#)." << std::endl << std::endl
				<< "The goal is to cross the board without dying." << std::endl;
	srand(time(NULL));
	std::string input, 
		clue;
	bool alpha;
	do {
		alpha = true;
		std::cout << std::endl << "Player 1: Enter the code string using only letters: " << std::endl;
		std::cin.clear();
		std::getline(std::cin, input);
		if (input.empty())
			alpha = false;
		else
			for (int i = 0; i <= input.length() - 1; i++)
				if (!isalpha(input[i]))
					alpha = false;
	} while (alpha == false);
	for (int i = 0; i < input.size(); i++)
	{
		char c = input[i];
		input[i] = toupper(c);
	}
	
	do {
		std::cout << "Player 1: Enter a clue for Player 2: " << std::endl;
		std::cin.clear();
		std::getline(std::cin, clue);
	} while (clue.empty());
	
	Board *b = new Board(input);
	Player *p = new Player(b->getMaxY()-1, (rand() % input.length()) * 2 + 1, b);
	while (p->getName() != input)
	{
		b->print();
		std::cout << "Clue: " << clue << std::endl;
		p->move();
		int length = (p->getName()).size() - 1;
		if (length != -1 && (p->getName())[length] != input[length])
			p->die();
	}
	b->print();
	p->move();
	b->print();
	std::cout << "The keyword was " << input << std::endl;
	std::cout << "You won losing " << p->getLives() << " lives!" << std::endl;
	return 0;
}