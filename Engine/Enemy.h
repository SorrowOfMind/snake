#pragma once

#include "Colors.h"
#include "Board.h"
#include "Location.h"
#include "Snake.h"
#include <random>

class Enemy
{
private:
	Location loc;
	static constexpr Color enemyColor = Colors::LightGray;
	static constexpr int nMaxEnemies = 15;
	static Enemy enemies[];
public:
	static int nActiveEnemies;
public:
	Enemy() {};
	Enemy(std::mt19937& rng, const Board& brd, const Location& goal);
	static void DrawEnemies(Board brd);
	static bool IsSnakeColliding(const Location& snakeLoc);
};