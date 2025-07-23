#pragma once
#include <iostream>
#include <unordered_map>
#include <utility>
#include <cmath>

constexpr float PI = 3.14159265f;

namespace Direction {

	enum dir {
		UP,
		UP_RIGHT,
		RIGHT,
		DOWN_RIGHT,
		DOWN,
		DOWN_LEFT,
		LEFT,
		UP_LEFT,
		STAY
	};

	struct Vector2D {
		int x, y;

		bool operator==(const Vector2D& other) const { //operator == between vector2D
			return (x == other.x && y == other.y);
		}
	};

	const Vector2D directionVectors[9] = {
	{0,-1}, // UP
	{1,-1}, //UP_RIGHT
	{1,0}, //RIGHT
	{1,1}, // DOWN_RIGHT
	{0,1}, //DOWN
	{-1,1}, //DOWN_LEFT
	{-1,0}, //LEFT
	{-1,-1}, //UP_LEFT
	{0,0} //STAY
	};

	const char directionCannonChars[9] = {
	'|', // UP
	'/', //UP_RIGHT
	'-', //RIGHT
	'\\', // DOWN_RIGHT
	'|', //DOWN
	'/', //DOWN_LEFT
	'-', //LEFT
	'\\', //UP_LEFT
	'0' //STAY
	};

	inline Direction::dir GetDirByName(Vector2D v) {
		for (int i = 0; i < 9; i++) {
			if (directionVectors[i] == v)
				return (Direction::dir)i;
		}
		return STAY;
	}


	/*
	Rotates a 2D vector (x, y) by a given angle in degrees.
	Returns the rotated vector with components rounded to nearest integers.
	*/
	inline Direction::Vector2D rotateVector(float x, float y, float angleDegrees) {
		float radians = angleDegrees * PI / 180.0f;
		float cosA = cos(radians);
		float sinA = sin(radians);

		float newX = x * cosA - y * sinA;
		float newY = x * sinA + y * cosA;

		// Round to nearest integer to keep values in {-1, 0, 1}
		int rx = std::round(newX);
		int ry = std::round(newY);

		return { rx, ry };
	}

};


// (U, UR, R, DR, D, DL, L, UL ,S)