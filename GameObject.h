#pragma once
//#include "Board.h"
#include "Point.h"
#include "Direction.h"

//class board;

class GameObject
{
public:
	bool IsObjectCross(const GameObject& other) const;

	virtual Point GetPos() const = 0;
	virtual Direction::dir GetDir() const = 0;
	bool IsObjectsCollide(const GameObject& other); // the function handle two moving points colliding in one of two cases: reaching the same point or crossing paths. return true if so.

};

