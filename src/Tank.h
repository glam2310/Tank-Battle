#pragma once
#include "Point.h"
#include "shell.h" 
#include "GameObject.h"

class Board;

class Tank : public GameObject
{
public:
	enum TrackMovement {
		TRACK_BACKWARD = -1,
		TRACK_STAYS = 0,
		TRACK_FORWARD = 1
	};

private:

	//DM:
	Point tank_pos; //where the tank located on the screen
	Point cannon_pos; //where the cannon located on the screen
	Direction::dir dir = Direction::UP; //It's to determine the direction vector of the tank's movement on the screen. represent the movment dir and the cannon_dir
	int trank_left = TRACK_STAYS; //It's for knowing which way the trank is moving.
	int trank_right = TRACK_STAYS; //It's for knowing which way the trank is moving.
	char cannon_char = '|';
	//int player;
	int shooting_cooldown_timer = 0;

	/*
	 shooting_cooldown_timer sync:
	  - When the tank shoots: set shooting_cooldown_timer to 5 (in HelperUpdateTrackMovement).
	  - When shoot key is pressed: if shooting_cooldown_timer > 0, shooting is not allowed.
	  - Each game loop: if shooting_cooldown_timer > 0, decrement it by 1 until it reaches 0.
	*/

	//Flegs
	bool has_a_cannon = true;
	bool alive = true;
	bool stay = true;

	/*
	STAY sync - spaciel status in which the tank stops:
	flag stay: get true.
	dir: no change. (save the dir that the tank is facing)
	trank_left and trank_right: get TRACK_STAYS.
	cannon pos: no change.
	tank_pos: no change.
	*/

	bool IsTankHitWall(Board& b); // fixed from Board* b to Board& b.
	bool IsTankSteOverAMine(Board& b);  // fixed from Board* b to Board& b. 
	//bool CheckHitOtherCannon(const std::vector<Tank>& player1, const std::vector<Tank>& player2);
	//bool CheckHitOtherBody(const std::vector<Tank>& player1, const std::vector<Tank>& player2);
public:

	Tank(Point _pos) :tank_pos(_pos) {
		cannon_pos = Point(tank_pos.getX(), tank_pos.getY() - 1, '|');
	};
	void draw() {
		tank_pos.draw();
		if (has_a_cannon)
			cannon_pos.draw();
	}

	void erase() {
		tank_pos.erase();
		cannon_pos.erase();
	}

	void SetTrankLeft(Tank::TrackMovement tm) {
		trank_left = tm;
	}

	virtual Direction::dir GetDir() const override {
		return dir;
	};

	void SetDir(Direction::dir d) {
		dir = d;
	}
	void Set_cannon_char(char ch) {
		cannon_char = ch;
	}
	void Set_cannon_pos(Point pos) {
		cannon_pos = pos;
	}
	void SetTrankRight(Tank::TrackMovement tm) {
		trank_right = tm;
	}

	void SetStay()
	{
		trank_left = TRACK_STAYS;
		trank_right = TRACK_STAYS;
		stay = true;
	}
	bool GetStay() {
		return stay;
	}
	void SetAlive(bool status)
	{
		alive = status;
	}
	void SetNotStay()
	{
		stay = false;
	}
	void DestroyCannon() {
		has_a_cannon = false;
		cannon_char = ' ';
	}
	int Get_shooting_cooldown_timer() const {
		return shooting_cooldown_timer;
	}

	void Set_shooting_cooldown_timer(int new_cooldown) {
		shooting_cooldown_timer = new_cooldown;
	}

	Point GetPos() const override {
		return tank_pos;
	};


	Point GetCannonPos() const
	{
		return cannon_pos;
	}

	bool Get_Alive() const {
		return alive;
	}
	bool Get_has_a_cannon() const
	{
		return has_a_cannon;
	}

	void CalcDir(Board& b); // fixed from Board* b to Board& b. 

	bool MoveTank(Board& b, const std::vector<Tank>& player1, const std::vector<Tank>& player2); // the func will return true if the tank body step over a mine
	void RestartTank(Point start_point);
	bool IsTankBodyStePOverAMine(Board& b);
	bool IsTankHitOtherTank(const std::vector<Tank>& player1, const std::vector<Tank>& player2);
};

