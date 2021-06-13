#pragma once

#include "Board.h"
#include <random>
#include "Enemy.h"

//will be represented with 2 classes: Snake class as a whole Entity and a class for a segment of the snake
class Snake
{
private:
	//we can declare a class inside another class
	//the outside world doesnt know about it
	class Segment
	{
	private:
		Location loc;
		Color c;
	public:
		void InitHead(const Location& loc);
		void InitBody(std::mt19937 rng);
		void Follow(const Segment& next);
		void Draw(Board& brd) const;
		void MoveBy(const Location& delta_loc);
		const Location& GetLocation() const; //it makes sense to return a reference here - const RefVar&
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow(std::mt19937 rng);
	void Draw(Board& brd) const;
	Location GetNextHeadLocation(const Location& delta_loc) const;
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;
	int GetActiveSegments() const;
	const Location& GetSegment(int index) const;
	Segment* GetSnake() { return segments; }
private:
	static constexpr int nSegmentsMax = 100;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr Color headColor = Colors::Yellow;
	Segment segments[nSegmentsMax];
	int nSegments = 1; //how many segments are currently active
};

