#include "pch.h"
#include "ZombieArena.h"
#include "zombie.h"

Zombie* createHorde(int numZombies, IntRect arena)
{
	Zombie* zombies = new Zombie[numZombies];
	int maxX = arena.width - 20, minX = arena.left + 20, maxY = arena.height - 20, minY = arena.top + 20;
	
	for (int i = 0; i < numZombies; i++) 
	{
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;
		switch (side)
		{
		case 0:
			x = minX;
			y = (rand() % maxY) + minY;
			break;
		case 1:
			x = maxX;
			y = (rand() % maxY) + minY;
			break;
		case 2:
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		case 3:
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		}
		srand((int)time(0) * i * 2);
		int type = (rand() % 3);
		zombies[i].spawn(x, y, type, i);

	}
	return zombies;
}