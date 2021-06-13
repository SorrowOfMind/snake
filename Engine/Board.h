#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
private:
	static constexpr int dimension = 20; //cells will be 20x20
	static constexpr int pad = 20;
	static constexpr int widthCells = (Graphics::ScreenWidth - pad) / dimension;
	static constexpr int heightCells = (Graphics::ScreenHeight - pad) / dimension;
	static constexpr int widthPx = Graphics::ScreenWidth - pad;
	static constexpr int heightPx = Graphics::ScreenHeight - pad;
	//lets cache the reference to the Graphics, so we won't pass it everytime
	//caching means storing locally for performance or convenience
	Graphics& gfx;
	static constexpr Color borderColor = Colors::Cyan;

	//Chilli solution
	//static constexpr x = 20;
	//static constexpr y = 20;

public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBorder();
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	int GetPad() const;
	int GetGridWidthPx() const;
	int GetGridHeightPx() const;
};