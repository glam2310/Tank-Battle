#pragma once
#include "Point.h"
#include "Direction.h"
#include "GameObject.h"

class Shell : public GameObject
{
	Direction::dir dir;
	Point pos;
	bool alive = true;

public:
	Shell(Direction::dir dir_, Point pos_) :dir(dir_), pos(pos_) {}; // does not have empty ctor on purpose
	void MoveShell();
	Point GetPos() const override {
		return pos;
	};

	Direction::dir GetDir() const override {
		return dir;
	};

	bool isShellCollidingWithShell(Shell sh);
	bool IsAlive() const {
		return alive;
	}
	void SetAlive(bool isAlive) { alive = isAlive; }

};


