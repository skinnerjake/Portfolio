/*************************************************************************
Name: Jake Skinner
Date: 10/31/16
Desc: This is the class defintion of Doodlebug
*************************************************************************/

#include "Doodlebug.hpp"
#include "Critter.hpp"
#include "World.hpp"

/*************************************************************************
Desc: Constructor for Doodlebug
*************************************************************************/
Doodlebug::Doodlebug(int y, int x, int b, World *w) : Critter(y, x, b, w)
{
	name = "Doodlebug";
	starveCounter = 3;
}

/*************************************************************************
Desc: Function tries to move the pointer to the Doodlebug to a random, 
		adjacent location in a 2D array. 
		- It will try to eat an adjacent ant
		- If not, it will try to move to an empty space
		- If not, it will remain in its original location
		The starve counter is decreased by 1.
*************************************************************************/
void Doodlebug::move(Direction d)
{
	int attempt = 0;
	starveCounter--;
	while ((attempt < 4) and (move_state == WAITING))
	{
		if (d == UP)
		{
			if (space->inBounds(row-1, col))
			{
				if (space->getCritter(row-1,col) != NULL)
				{
					if (space->getCritter(row-1, col)->getName() == "Ant")
					{
						space->starveDoodlebug(row-1, col);
						space->setCritter(row-1, col, this);
						space->setCritter(row, col, NULL);
						row--;
						move_state = MOVED;
						starveCounter = 3;
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
				if (space->getCritter(row,col+1) != NULL)
				{
					if (space->getCritter(row, col+1)->getName() == "Ant")
					{
						space->starveDoodlebug(row, col+1);
						space->setCritter(row, col+1, this);
						space->setCritter(row, col, NULL);
						col++;
						move_state = MOVED;
						starveCounter = 3;
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
				if (space->getCritter(row+1,col) != NULL)
				{
					if (space->getCritter(row+1, col)->getName() == "Ant")
					{
						space->starveDoodlebug(row+1, col);
						space->setCritter(row+1, col, this);
						space->setCritter(row, col, NULL);
						row++;
						move_state = MOVED;
						starveCounter = 3;
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
				if (space->getCritter(row,col-1) != NULL)
				{
					if (space->getCritter(row, col-1)->getName() == "Ant")
					{
						space->starveDoodlebug(row, col-1);
						space->setCritter(row, col-1, this);
						space->setCritter(row, col, NULL);
						col--;
						move_state = MOVED;
						starveCounter = 3;
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
			else
			{
				attempt++;
				d = UP;
			}
		}
	}
	
	attempt = 0;
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
Desc: The doodlebug will try to breed every 8 turns into a random, empty
		adjacent location. If not, it does nothing.
*************************************************************************/
void Doodlebug::breed(Direction d)
{
	int now = space->getTurns();
	if ((birthday != now) and ((birthday-now) % 8 == 0))
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
						space->newDoodlebug(row-1, col);
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
						space->newDoodlebug(row, col+1);
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
						space->newDoodlebug(row+1, col);
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
						space->newDoodlebug(row, col-1);
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

/*************************************************************************
Desc: If the doodlebug has not eaten in 3 turns, it will be deleted from
		the board
*************************************************************************/
bool Doodlebug::starve()
{
	if (starveCounter <=0)
		return true;
	else
		return false;
}