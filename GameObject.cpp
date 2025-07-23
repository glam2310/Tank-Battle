#include "GameObject.h"
using namespace Direction;

bool GameObject::IsObjectCross(const GameObject& other)const
{ //The function checks if two objects are crossing paths(meaning they never shared the same point but still collided)
	Point prev_pos = GetPos();
	prev_pos.setX(prev_pos.getX() + (directionVectors[GetDir()].x * -1));
	prev_pos.setY(prev_pos.getY() + (directionVectors[GetDir()].y * -1));

	Point other_prev_pos = other.GetPos();
	other_prev_pos.setX(other_prev_pos.getX() + (directionVectors[other.GetDir()].x * -1));
	other_prev_pos.setY(other_prev_pos.getY() + (directionVectors[other.GetDir()].y * -1));

	if (prev_pos == other.GetPos() && other_prev_pos == GetPos())
		return true;
	return false;


}

bool GameObject::IsObjectsCollide(const GameObject& other) {
	if (GetPos() == other.GetPos())
		return true;
	if (IsObjectCross(other))
		return true;
	return false;
}
