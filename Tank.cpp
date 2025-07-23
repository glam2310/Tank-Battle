#include "Tank.h"
#include "Board.h"
using namespace Direction;

bool Tank::IsTankHitWall(Board& b)
{

	/*note that - if a tank is moving and hits a wall, it should stop at the wall
	but remain ready to move in any other valid direction when the player presses a different movement key
	*/

	// Check tank's next position
	Point tank_check_point = tank_pos;
	tank_check_point.move(dir);

	if (trank_left == trank_right && trank_right == TRACK_BACKWARD) //check if hit a wall in this case (body of the tank hit first)
	{
		Point reverse_check_point = tank_pos;
		reverse_check_point.move(GetDirByName({ (-1) * directionVectors[dir].x,  (-1) * directionVectors[dir].y }));
		if (b.clashAWall(reverse_check_point) || b.clashAWeakWall(reverse_check_point))
			return true;
		else
			return false;
	}

	// Check if tank would hit a wall
	if (b.clashAWall(tank_check_point) || b.clashAWeakWall(tank_check_point))
		return true;



	// If has cannon, check if the cannon would hit a wall after moving the tank
	if (has_a_cannon) {
		Point cannon_check_point = tank_check_point; // Start from tank's new position
		cannon_check_point.move(dir); // Move once more for cannon
		if (b.clashAWall(cannon_check_point) || b.clashAWeakWall(cannon_check_point))
			return true;
	}

	return false;

}

bool Tank::IsTankSteOverAMine(Board& b) // using this method after moving the tank to a new pos!!
{
	if (b.getChar(cannon_pos) == '@')
		return true;
	return false;
}



bool Tank::IsTankBodyStePOverAMine(Board& b) // using this method to kill tank 
{
	if (b.getChar(tank_pos) == '@')
		return true;
	return false;
}

bool Tank::IsTankHitOtherTank(const std::vector<Tank>& player1, const std::vector<Tank>& player2) // here the current tankl (this*) need to know the other's positions in ordedr to implemnt the checks for Tank::Move
{
	for (const Tank& tank : player1) {
		if (&tank == this)
			continue;
		if (tank_pos == tank.tank_pos || tank_pos == tank.cannon_pos || cannon_pos == tank.cannon_pos || cannon_pos == tank.tank_pos)
			return true;
	}

	for (const Tank& tank : player2) {
		if (&tank == this)
			continue;
		if (tank_pos == tank.tank_pos || tank_pos == tank.cannon_pos || cannon_pos == tank.cannon_pos || cannon_pos == tank.tank_pos)
			return true;
	}
	return false;

}




bool Tank::MoveTank(Board& b, const std::vector<Tank>& player1, const std::vector<Tank>& player2) {
	if (stay)
		return false;
	//if (IsTankHitWall(b))
		//return false;
	//if (IsTankHitOtherTank(player1, player2)) {
	//	SetStay();
		//return false;
	//}
	Point prev_tank_pos = tank_pos;
	Point prev_cannon_pos = cannon_pos;
	char prev_cannon_char = cannon_char;

	if (trank_left == TRACK_FORWARD && trank_right == TRACK_FORWARD) { //forward case 
		tank_pos.move(dir); //update the next pos of the tank(according to dir)
		//cannon_pos = tank_pos; // cannon is one step ahead in the dir of tank , so w'll assign the value of tank_pos into cannon_pos and the opearte Move one more time 
		//cannon_pos.move(dir);
		SetNotStay();
	}

	if (trank_left == TRACK_BACKWARD && trank_right == TRACK_BACKWARD) { //revres case
		tank_pos.move(GetDirByName({ (-1) * directionVectors[dir].x,  (-1) * directionVectors[dir].y }));
		SetNotStay();

	}

	if (has_a_cannon) {
		cannon_pos = tank_pos; // cannon is one step ahead in the dir of tank , so w'll assign the value of tank_pos into cannon_pos and the opearte Move one more time 
		cannon_pos.move(dir);
		//change the cannon char according the dir 
		cannon_pos.setChar(directionCannonChars[dir]);
	}
	
	if (b.clashAWall(cannon_pos) || b.clashAWeakWall(cannon_pos) || b.clashAWall(tank_pos) || b.clashAWeakWall(tank_pos))
	{
		//fall back
		cannon_char = prev_cannon_char;
		tank_pos = prev_tank_pos;
		cannon_pos = prev_cannon_pos;
	}

	if (IsTankHitOtherTank(player1, player2))
	{
		//fall back
		cannon_char = prev_cannon_char;
		tank_pos = prev_tank_pos;
		cannon_pos = prev_cannon_pos;
		SetStay();
	}

	if (IsTankBodyStePOverAMine(b)) { // check if the tank step over a mine and change status to not alive
		alive = false;
		return true;
	}
	return false;
}

void Tank::RestartTank(Point start_point) //get defalut pos 
{
	//tank instants restart
	tank_pos = start_point;
	cannon_pos = Point(tank_pos.getX(), tank_pos.getY() - 1, '|');
	dir = Direction::UP;
	trank_left = TRACK_STAYS;
	trank_right = TRACK_STAYS;
	cannon_char = '|';
	shooting_cooldown_timer = 0;
	has_a_cannon = true;
	alive = true;
	stay = true;

}


/*
input: get the last dir and the trank movment - output:
the func calc the new dir and change it
*/
void Tank::CalcDir(Board& b)
{
	Direction::dir prev_dir = dir; // save the prev dir

	if (stay)
		return; //  save unnecessary work

	if (trank_left == TRACK_STAYS && trank_right == TRACK_STAYS) // Remember to set the 'stay' flag to true as soon as the corresponding button is pressed, Then it's unnecessary.
		stay = true;


	if (trank_left == TRACK_FORWARD && trank_right == TRACK_FORWARD)
		return; //it's unnecessary - save the last dir



	if (trank_left == TRACK_BACKWARD && trank_right == TRACK_BACKWARD)
	{
		//dir = GetDirByName({ (-1) * directionVectors[dir].x,  (-1) * directionVectors[dir].y })
		//trank_left = trank_right = TRACK_FORWARD; //
		//if (IsTankHitWall(b)) // check if the move is valid , if not return to the prev dir
			//dir = prev_dir;

	}

	if (trank_left == TRACK_STAYS && trank_right == TRACK_FORWARD) { //Rotate counter-clockwise in place 
		dir = GetDirByName(rotateVector(directionVectors[dir].x, directionVectors[dir].y, -45)); //  // 45 degrees to the left
	
	}

	if (trank_left == TRACK_BACKWARD && trank_right == TRACK_FORWARD) { //Rotate counter-clockwise in place
		dir = GetDirByName(rotateVector(directionVectors[dir].x, directionVectors[dir].y, -90)); //  // 90 degrees to the left
		
	}

	if (trank_left == TRACK_FORWARD && trank_right == TRACK_STAYS) { //Rotate counter-clockwise in place
		dir = GetDirByName(rotateVector(directionVectors[dir].x, directionVectors[dir].y, 45));//  // 45 degrees to the right
	
	}

	if (trank_left == TRACK_FORWARD && trank_right == TRACK_BACKWARD) { //Rotate counter-clockwise in place
		dir = GetDirByName(rotateVector(directionVectors[dir].x, directionVectors[dir].y, 90)); //  // 90 degrees to the right
		
	}

	if (trank_left == TRACK_STAYS && trank_right == TRACK_BACKWARD) { //Rotate counter-clockwise in place
		dir = GetDirByName(rotateVector(directionVectors[dir].x, directionVectors[dir].y, 45)); //  // 45 degrees to the right
	
	}

	if (trank_left == TRACK_BACKWARD && trank_right == TRACK_STAYS) { //Rotate counter-clockwise in place
		dir = GetDirByName(rotateVector(directionVectors[dir].x, directionVectors[dir].y, -45)); //  // 45 degrees to the left
		
	}



}







