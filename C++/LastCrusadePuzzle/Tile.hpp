/***************************************************************************************
Name: Jake Skinner
Date: 12/6/16
Desc: This file contains the declaration for class Tile
***************************************************************************************/

#ifndef TILE_HPP
#define TILE_HPP

#include "Space.hpp"
#include <string>

enum Sightline {FOG, CLEAR};

class Tile : public Space
{
	private:
		static const char bank[];
		static const int bankSize = 26;
		Sightline exposed;
	public:
		Tile(int, int, Board*);
		~Tile() {}
		void print();
		void setLetter(char l) {letter = l;}
};

#endif