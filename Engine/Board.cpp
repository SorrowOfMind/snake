#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= (pad / dimension));
	assert(loc.x < widthCells);
	assert(loc.y >= (pad / dimension));
	assert(loc.y < heightCells);

	//Chilli code
	/*const int off_x = x;
	const int off_y = y;
	gfx.DrawRectDim(loc.x * dimension + off_x, loc.y * dimension + off_y, dimension, dimension, c);*/

	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension, dimension, c);
}
void Board::DrawBorder() //int x0, int y0, int x1, int y1, Color c
{
	gfx.DrawBorder(pad, pad, widthPx, heightPx, borderColor);
}


int Board::GetGridWidth() const
{
	return widthCells;
}

int Board::GetGridHeight() const
{
	return heightCells;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= (pad / dimension) && loc.x < widthCells
			&& loc.y >= (pad / dimension) && loc.y < heightCells;
}

int Board::GetPad() const
{
	return pad;
}

int Board::GetGridWidthPx() const
{
	return widthPx;
}

int Board::GetGridHeightPx() const
{
	return heightPx;
}

