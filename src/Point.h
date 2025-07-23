#pragma once
#include <iostream>
#include "Utils.h"
#include "Direction.h"

class Point
{
	int x;
	int y;
	char ch;

	void private_draw(char ch) {
		gotoxy();
		std::cout << ch;
	}

public:
	Point(int _x = 1, int _y = 1, char _ch = 'O') :x(_x), y(_y), ch(_ch) {}; //c'tor

	void gotoxy() const;

	void setX(int x1) {
		x = x1;
	}

	void setY(int y1) {
		y = y1;
	}

	void setChar(char c) {
		ch = c;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}

	int getCh() {
		return ch;
	}

	void draw() {
		private_draw(ch);
	}
	void erase() {
		draw(' ');
	}
	void move(Direction::dir d, int max_x = 80, int max_y = 25);

	void draw(char c) { // draw space bar at point
		private_draw(c);
	}

	bool operator==(const Point& other) const
	{
		return (x == other.x && y == other.y);
	}

	bool IsVertical(const Point& other) const {
		return ((x == other.x || y == other.y));
	}

};


