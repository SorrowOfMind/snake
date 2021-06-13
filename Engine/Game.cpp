/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake({ 4,4 }), //initialize snake with constructor(location)
	goal(rng,brd,snake),
	snakeMovePeriod(20),
	enemyPeriod(360)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

int Game::SetSnakeMovePeriod(int value)
{
	return snakeMovePeriod -= value;
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_RETURN) && !gameIsStarted)
		gameIsStarted = true;

	if (!gameIsOver && gameIsStarted)
	{
		//keyboard input
		if (wnd.kbd.KeyIsPressed(VK_UP))
			delta_loc = { 0, -1 };
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			delta_loc = { 0, 1 };
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			delta_loc = { -1, 0 };
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			delta_loc = { 1, 0 };

		++snakeMoveCounter;
		if (snakeMoveCounter >= snakeMovePeriod)
		{
			snakeMoveCounter = 0;
			const Location next = snake.GetNextHeadLocation(delta_loc);
			if (!brd.IsInsideBoard(next) || snake.IsInTileExceptEnd(next) || Enemy::IsSnakeColliding(next))
				gameIsOver = true;
			else
			{
				const bool eating = next == goal.GetLocation();
				if (eating)
				{
					snake.Grow(rng);
					if (snake.GetActiveSegments() % 4 == 0 && snakeMovePeriod >= 0)
						SetSnakeMovePeriod(1);
				}
					
				snake.MoveBy(delta_loc);
				if (eating)
					goal.Respawn(rng, brd, snake);
			}
		}

		++enemyCounter;
		if (enemyCounter >= enemyPeriod)
		{
			enemyCounter = 0;
			Enemy e(rng, brd, goal.GetLocation());
		}

	}

}

void Game::ComposeFrame()
{
	//TEST CODE!
	//std::uniform_int_distribution<int> colorDist(0, 255);
	//for (int y = 0; y < brd.GetGridHeight(); y++)
	//{
	//	for (int x = 0; x < brd.GetGridWidth(); x++)
	//	{
	//		//for each cell create a location obj and a color object randomy generated from a color dist
	//		//Location struct doesn't have a constructor, we can only initialize structs/classes with {} if
	//		//they have no private data and specify no constructors.
	//		Location loc = { x,y };
	//		Color c(colorDist(rng), colorDist(rng), colorDist(rng));
	//		brd.DrawCell(loc, c);
	//	}
	//}
	if (!gameIsStarted)
	{
		SpriteCodex::DrawTitle((Graphics::ScreenWidth / 2) - 100, (Graphics::ScreenHeight / 2) - 100, gfx);
	}
	else
	{
		brd.DrawBorder();
		snake.Draw(brd);
		goal.Draw(brd);
		if (Enemy::nActiveEnemies > 0)
			Enemy::DrawEnemies(brd);
	}

	if (gameIsOver)
	{
		SpriteCodex::DrawGameOver((Graphics::ScreenWidth / 2) - 50, (Graphics::ScreenHeight / 2) - 50, gfx);
	}
}
