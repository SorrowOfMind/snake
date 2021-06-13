#include "Enemy.h"

int Enemy::nActiveEnemies = 0;
Enemy Enemy::enemies[Enemy::nMaxEnemies];

Enemy::Enemy(std::mt19937& rng, const Board& brd, const Location& goal)
{
	if (nActiveEnemies < nMaxEnemies)
	{
		std::uniform_int_distribution<int> xDist(1, brd.GetGridWidth() - 1);
		std::uniform_int_distribution<int> yDist(1, brd.GetGridHeight() - 1);

		loc.x = xDist(rng);
		loc.y = yDist(rng);

		//check if enemy is not spawned on the goal or snake
		while (loc.x == goal.x && loc.y == goal.y)
		{
			loc.x = xDist(rng);
			loc.y = yDist(rng);
		}

		enemies[nActiveEnemies] = *this;

		++nActiveEnemies;
	}
}

void Enemy::DrawEnemies(Board brd)
{
	for (int i = 0; i < nActiveEnemies; ++i)
	{
		brd.DrawCell(enemies[i].loc, enemyColor);
	}
}

bool Enemy::IsSnakeColliding(const Location& snakeLoc)
{
	for (int i = 0; i < nActiveEnemies; ++i)
	{
		int enemyX = enemies[i].loc.x;	
		int enemyY = enemies[i].loc.y;
		
		if (snakeLoc.x == enemyX && snakeLoc.y == enemyY)
			return true;
	}
	return false;
}
