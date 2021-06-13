#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	//we move from tail!
	for (int i = nSegments - 1; i > 0; i--)
	{
		//follow the segment before
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow(std::mt19937 rng)
{
	if (nSegments < nSegmentsMax)
	{
		segments[nSegments].InitBody(rng);
		++nSegments;
	}
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(brd);
	}
}

Location Snake::GetNextHeadLocation(const Location& delta_loc) const
{
	//copy constructor
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

bool Snake::IsInTileExceptEnd(const Location& target) const
{
	for (int i = 0; i < nSegments - 1; i++)
	{
		if (segments[i].GetLocation() == target) //== no operation defined to compare 2 locations (Location is our own type), we need to define it
			return true;
	}
	return false;
}

bool Snake::IsInTile(const Location& target) const
{
	for (int i = 0; i < nSegments ; i++)
	{
		if (segments[i].GetLocation() == target) //== no operation defined to compare 2 locations (Location is our own type), we need to define it
			return true;
	}
	return false;
}

int Snake::GetActiveSegments() const
{
	return nSegments;
}

const Location& Snake::GetSegment(int index) const
{
	return segments[index].GetLocation();
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(std::mt19937 rng)
{
	std::uniform_int_distribution<int> greenDist(100, 255);
	c = Color(0, greenDist(rng), 0);
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
