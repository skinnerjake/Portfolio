/***************************************************************************************
Name: Jake Skinner
Date: 12/6/16
Desc: This file contains the member definitions for the class Space
***************************************************************************************/

#include "Space.hpp"
#include <cstdlib>
#include <iostream>

Space::Space(int y_, int x_, Board *a)
{
	x = x_;
	y = y_;
	area = a;
	opening = VACANT;	
}

/*

Superclass: Space
Subclasses:
	- Path
		- 
	- Edge: Corner, side, top, 
	- Ledge
		- move laterally
		- win game
	- *Hole == NULL


Class Player

key:



 1  2  3
  \ | /
 4<-@->5
 
 1  2
  \ |
 4<-@
 
    2  3
    | /
    @->5
    
 1  2  3
  \ | /
    @
    
    2  3
    | /
    @
    
 1  2
  \ |
    @

    2
    |
    @



Board:

    END
   @
===|=========
|A|B|C|D|E|F|
+-+|+-+-+-+-+
|G|H|I|J|K|L|
+-+-\-+-+-+-+
|M|#|#|#|#|#|
+-+-+-\-+-+-+
|?|?|?|?-?|?|
+-+-+-/-+-+-+
| | | | | | |
+-+-+-\-+-+-+
| | | | | | |
=======|=====
       @
	START

1-Player
   or
2-Player

2 player: 
	Player1: Choose difficulty
	Player2: Enter alphanumeric string with no spaces
	Player2: Enter a hint
*/