/*************************************************************************
Name: Jake Skinner
Date: 10/31/16
Desc: This is the class definition of Ant
*************************************************************************/

#include "Ant.hpp"
#include "Critter.hpp"

/*************************************************************************
Desc: Constructor for Ant
*************************************************************************/
Ant::Ant(int y, int x, int b, World *w) : Critter(y, x, b, w)
{
	name = "Ant";
}

/*************************************************************************
Desc: Function tries to move the pointer to the Ant to a random, adjacent 
		location in a 2D array. 
		- It will try to move to an empty space
		- If not, it will remain in its original location
*************************************************************************/
void Ant::move(Direction d)
{
	int attempt = 0;
	while ((attempt < 4) and (move_state == WAITING))
	{
		if (d == UP)
		{
			if (space->inBounds(row-1, col))
			{
				if (space->getCritter(row-1,col) == NULL)
				{
					space->setCritter(row-1, col, this);
					space->setCritter(row, col, NULL);
					row--;
					move_state = MOVED;
				}
				else
				{
					attempt++;
					d = RIGHT;
				}
			}
			else
			{
				attempt++;
				d = RIGHT;
			}
		}
		
		else if (d == RIGHT)
		{
			if (space->inBounds(row, col+1))
			{
				if (space->getCritter(row,col+1) == NULL)
				{
					space->setCritter(row, col+1, this);
					space->setCritter(row, col, NULL);
					col++;
					move_state = MOVED;
				}
				else
				{
					attempt++;
					d = DOWN;
				}
			}
			else
			{
				attempt++;
				d = DOWN;
			}
		}
	
		else if (d == DOWN)
		{
			if (space->inBounds(row+1, col))
			{
				if (space->getCritter(row+1,col) == NULL)
				{
					space->setCritter(row+1, col, this);
					space->setCritter(row, col, NULL);
					row++;
					move_state = MOVED;
				}
				else
				{
					attempt++;
					d = LEFT;
				}
			}
			else
			{
				attempt++;
				d = LEFT;
			}
		}
	
		else if (d == LEFT)
		{
			if (space->inBounds(row, col-1))
			{
				if (space->getCritter(row,col-1) == NULL)
				{
					space->setCritter(row, col-1, this);
					space->setCritter(row, col, NULL);
					col--;
					move_state = MOVED;
				}
				else
				{
					attempt++;
					d = UP;
				}
			}
			else
			{
				attempt++;
				d = UP;
			}
		}
	}
	if (move_state == WAITING)
		move_state = MOVED;
}

/*************************************************************************
Desc: The Ant will try to breed every 3 turns into a random, empty
		adjacent location. If not, it does nothing.
*************************************************************************/
void Ant::breed(Direction d)
{
	int now = space->getTurns();
	if ((birthday != now) and ((birthday-now) % 3 == 0))
	{
		int attempt = 4;
		while (attempt > 0)
		{
			if (d == UP)
			{
				if (space->inBounds(row-1, col))
				{
					if (space->getCritter(row-1, col) == NULL)
					{
						space->newAnt(row-1, col);
						attempt = 0;
					}
					else
					{
						attempt--;
						d = RIGHT;
					}
				}
				else
				{
					attempt--;
					d = RIGHT;
				}
			}
			else if (d == RIGHT)
			{
				if (space->inBounds(row, col+1))
				{
					if (space->getCritter(row, col+1) == NULL)
					{
						space->newAnt(row, col+1);
						attempt = 0;
					}
					else
					{
						attempt--;
						d = DOWN;
					}
				}
				else
				{
					attempt--;
					d = DOWN;
				}
			}
			else if (d == DOWN)
			{
				if (space->inBounds(row+1, col))
				{
					if (space->getCritter(row+1, col) == NULL)
					{
						space->newAnt(row+1, col);
						attempt = 0;
					}
					else
					{
						attempt--;
						d = LEFT;
					}
				}
				else
				{
					attempt--;
					d = LEFT;
				}
			}
			else if (d == LEFT)
			{
				if (space->inBounds(row, col-1))
				{
					if (space->getCritter(row, col-1) == NULL)
					{
						space->newAnt(row, col-1);
						attempt = 0;
					}
					else
					{
						attempt--;
						d = UP;
					}
				}
				else
				{
					attempt--;
					d = UP;
				}
			}
		}
	}
}