#include "Point.h"

using namespace Direction;


void Point::move(dir d, int max_x, int max_y) {
	switch (d) {
	case UP:
		y = (max_y + (y - 1)) % max_y;
		break;
	case LEFT:
		x = (max_x + (x - 1)) % max_x;
		break;
	case DOWN:
		y = (y + 1) % max_y;
		break;
	case RIGHT:
		x = (x + 1) % max_x;
		break;
	case UP_RIGHT:
		y = (max_y + (y - 1)) % max_y;
		x = (x + 1) % max_x;
		break;
	case DOWN_RIGHT:
		y = (y + 1) % max_y;
		x = (x + 1) % max_x;
		break;
	case DOWN_LEFT:
		y = (y + 1) % max_y;
		x = (max_x + (x - 1)) % max_x;
		break;
	case UP_LEFT:
		y = (max_y + (y - 1)) % max_y;
		x = (max_x + (x - 1)) % max_x;
		break;
	case STAY:
		break;
	}
}

void Point::gotoxy() const {
	std::cout.flush();
	COORD coord; // Create a COORD structure 
	coord.X = x; // Set the X coordinate 
	coord.Y = y; // Set the Y coordinate 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}

