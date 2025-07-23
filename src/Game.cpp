#include "Game.h"

const Point Game::default_player1 = Point(14, 22);
const Point Game::default_player2 = Point(50, 22);

/*
The function gets a character and checks if it's one of the
player's keys - if so, it changes the matching direction according
to the movement the key represents or enables the shooting flag.
*/
void Game::HelperUpdateTrackMovement(char ch)
{
	switch (ch)
	{
		// First player keys
	case 'E':
		//player1.SetTrankRight(Tank::TRACK_FORWARD);
		player1[index_player1].SetTrankRight(Tank::TRACK_FORWARD);
		//player1.SetNotStay();
		player1[index_player1].SetNotStay();
		break;
	case 'D':
		//player1.SetTrankRight(Tank::TRACK_BACKWARD);
		player1[index_player1].SetTrankRight(Tank::TRACK_BACKWARD);
		//player1.SetNotStay();
		player1[index_player1].SetNotStay();
		break;
	case 'Q':
		//player1.SetTrankLeft(Tank::TRACK_FORWARD);
		player1[index_player1].SetTrankLeft(Tank::TRACK_FORWARD);
		//player1.SetNotStay();
		player1[index_player1].SetNotStay();
		break;
	case 'A':
		//player1.SetTrankLeft(Tank::TRACK_BACKWARD);
		player1[index_player1].SetTrankLeft(Tank::Tank::TRACK_BACKWARD);

		//player1.SetNotStay();
		player1[index_player1].SetNotStay();
		break;

	case 'S':
		//player1.SetStay();
		player1[index_player1].SetStay();
		break;
	case 'W':
		// shoot case 
	{  	addShell(player1[index_player1]);
	break;
	}
	case 'Z':
	{
		player1[index_player1].SetNotStay();
		advanceIndex(index_player1, player1.size()); // Moves to the next tank in player1
		break;
	}

	// Second plkayer keys
	case 'O':
		//player2.SetTrankRight(Tank::TRACK_FORWARD);
		player2[index_player2].SetTrankRight(Tank::TRACK_FORWARD);

		//player2.SetNotStay();
		player2[index_player2].SetNotStay();

		break;
	case 'L':
		//player2.SetTrankRight(Tank::TRACK_BACKWARD);
		player2[index_player2].SetTrankRight(Tank::TRACK_BACKWARD);

		//player2.SetNotStay();
		player2[index_player2].SetNotStay();
		break;

	case 'U':
		//player2.SetTrankLeft(Tank::TRACK_FORWARD);
		player2[index_player2].SetTrankLeft(Tank::TRACK_FORWARD);
		//player2.SetNotStay();
		player2[index_player2].SetNotStay();
		break;
	case 'J':
		//player2.SetTrankLeft(Tank::TRACK_BACKWARD);
		player2[index_player2].SetTrankLeft(Tank::TRACK_BACKWARD);

		//player2.SetNotStay();
		player2[index_player2].SetNotStay();
		break;
	case 'K': // Note: This should probably be 'K' for consistency
		//player2.SetStay();
		player2[index_player2].SetStay();
		break;
	case 'I':
		// shoot case 
	{  	addShell(player2[index_player2]);

	break;
	}
	case 'M':
	{
		player2[index_player2].SetNotStay();
		advanceIndex(index_player2, player2.size()); // Moves to the next tank in player2
		break;
	}
	default:
		break;
	}
}




void Game::KbhitAndGetch_(char* keys) // the func take max of 6 chars from the buffer into keys array
{
	for (int i = 0; i < SIX; i++)
	{
		if (_kbhit() && i < SIX)
			keys[i] = toupper(_getch()); // convert cher to upper case letter and insert into keys
		else
			return;
	}

	void Flush(); //clean the buffer 
}



/*
 review the input keys and (using helper fuc) change the trank dir
 if there is char that fit's the players keys
*/
void Game::UpdateTrackMovement(char* keys)
{
	bool stay = false; //if stay key was pressed allow only stay keys to be updated
	for (int i = 0; i < SIX; i++)
	{
		if (keys[i] == 'S' || keys[i] == 'K')
			stay = true;

		if (stay) {
			if (keys[i] == 'S' || keys[i] == 'K') {
				HelperUpdateTrackMovement(keys[i]);
			}
			else
				continue;
		}
		if (!stay)
			HelperUpdateTrackMovement(keys[i]);
	}
	for (int i = 0; i < SIX; i++)
	{
		keys[i] = '0'; //clean the array!!! 
	}
}

void Game::main_menu() {
	Flush(); // cleaning buffer
	hideCursor();
	char key;
	b.fillStageMenuBoard(stages); // once the game obj is born this screen never chages , so we call it here one time 
	while (true)
	{
		//b.reset(board_type::MAIN_MENU); // set curr board to main menu
		b.print(Board::Board_Type::MAIN_MENU, ""); // print board to screen 
		key = _getch(); // wait for key from user
		if (key == PLAY) {
			int mode = game_mode_board();
			if (mode == '2')
				break;
			set_mode(mode);
			restart_game();
			Run(1);
			continue;
		}
		if (key == SCREENS) {
			restart_game();
			int stage_number = stages_menu();
			if (stage_number == ZERO)
				continue;
			else {
				Run(stage_number);
				continue;
			}
		}
		else if (key == INSTRUCTIONS) {
			instructions_menu();
			//b.reset(board_type::MAIN_MENU);
			//b.print(board_type::INSTRUCTIONS);
		}
		else if (key == EXIT) { //9==EXIT
			break;
		}
		Flush();
	}
}

void Game::restart_game() {
	Flush(); // cleaning buffer
	//player1.RestartTank(default_player1); //resrt tank - no need because i create new tanks each level here -  Board::checkCharFromBoard
	//player2.RestartTank(default_player2);// resrt tank - no need because i create new tanks each level here -  Board::checkCharFromBoard

	//game instants restart
	winner_massge = "";
	index_player1 = ZERO;
	index_player2 = ZERO;
	RestartShells();

}

void Game::instructions_menu() {
	//	b.reset(board_type::INSTRUCTIONS);
	b.print(Board::Board_Type::INSTRUCTIONS, "");
	while (_getch() != (int)Board::Board_Type::MAIN_MENU); // display instructions menu until 2 is preesed
	Flush();
}





int Game::stages_menu() {
	b.print(Board::Board_Type::STAGES, "");

	int stage_num = -1;
	char key;

	while (true) {
		key = _getch();


		if (key >= '0' && key <= '9') {
			stage_num = key - '0';
			if (stage_num <= static_cast<int>(stages.size()))
				break;
		}
	}

	Flush();
	return stage_num;
}



void Game::end_game_board() {

	b.print(Board::Board_Type::END_OF_GAME, winner_massge, winner_score);
	while (_getch() != (int)Board::Board_Type::MAIN_MENU); // display instructions menu until 2 is preesed
	Flush();
}

int Game::end_level_board() {
	
	b.print(Board::Board_Type::END_OF_LEVEL, winner_massge, winner_score);

	char key;
	while (true) {
		key = _getch();

		if (key == '2') {
			return 2; // back to main menu
		}
		else if (key == '1') {
			return 1; // next level
		}

	}

}



void Game::addShell(Tank& player)
{
	if (!player.Get_has_a_cannon()) return; // tank can not shoot shells after losing its cannon 
	Point shell_pos = player.GetCannonPos();
	shell_pos.setChar('*');
	Direction::dir shell_dir = player.GetDir();
	Shell new_shell = Shell(shell_dir, shell_pos);
	shells.push_back(new_shell);
	player.Set_shooting_cooldown_timer(FIVE);
}

void Game::UpdateShootingCooldowns() {
	applyToAllTanks(player1, [](Tank& t) {
		if (t.Get_shooting_cooldown_timer() > 0) {
			t.Set_shooting_cooldown_timer(t.Get_shooting_cooldown_timer() - 1);
		}
		});

	applyToAllTanks(player2, [](Tank& t) {
		if (t.Get_shooting_cooldown_timer() > 0) {
			t.Set_shooting_cooldown_timer(t.Get_shooting_cooldown_timer() - 1);
		}
		});
}





void Game::MoveShells() { // for speed we will call MoveShell twice here , and do the checks twice
	bool hit = false;
	for (Shell& shell : shells) {
		//	if (!b.clashAWall(shell.GetPos()))// if orignaly there is no wall 
		b.restoreFromCurrentBoard(shell.GetPos());
		shell.MoveShell();
		//checks
		shell.GetPos().draw();
		CheckShellsMovement(shell, hit);
		Sleep(70);
		//if(b.getChar(shell.GetPos()) != '#') // if you are not a wall point orignaly
		b.restoreFromCurrentBoard(shell.GetPos());
	
		if (!hit) { // another round for a signal shell that still alive
			for (Shell& shell : shells) {
				shell.MoveShell();
				//checks
				shell.GetPos().draw();
				CheckShellsMovement(shell, hit);
				Sleep(70);
				b.restoreFromCurrentBoard(shell.GetPos());
			}
			
		}
		RemoveDeadShells();
	}
}


void Game::ShellCollidingWithTank(Shell& sh, bool& isHit) { // if shell hit the bosgy tank the shell and the tank is no longer alive

	for (Tank& t : player1) {
		if (sh.GetPos() == t.GetPos() && sh.IsAlive()) {
			t.SetAlive(false);     // Kill tank - tank is killed is removed from the vector at the end of Game::Run 
			sh.SetAlive(false);    // Kill shell
			isHit = true;
			break; // Exit early once hit - After the shell hits one tank, it's no longer active
		}
	}


	// Check collision with all player2 tanks
	for (Tank& t : player2) {
		if (sh.GetPos() == t.GetPos() && sh.IsAlive()) {
			t.SetAlive(false);     // Kill tank
			sh.SetAlive(false);    // Kill shell
			isHit = true;
			break; // Exit early once hit - After the shell hits one tank, it's no longer active
		}
	}

}

void Game::ShellCollidingWithWall(Shell& sh, bool& isHit)
{
	Point pos = sh.GetPos();
	if (b.clashAWall(pos) && sh.IsAlive()) {
		sh.SetAlive(false);// kill shell
		b.WeakenWall(pos); // Weaken Wall
		return;
	}
	if (b.getCharFromCurrentBoard(pos) == '=')
	{
		sh.SetAlive(false); //kill shell
		b.DeleteWeakWall(pos); //delete wall
	}

}



void Game::ShellCollidingWithCannon(Shell& sh, bool& isHit) {
	// Check all player1 tanks
	applyToAllTanks(player1, [&](Tank& t) {
		if (t.Get_has_a_cannon() && sh.GetPos() == t.GetCannonPos() && sh.IsAlive()) {
			t.DestroyCannon();     // kill the cannon
			sh.SetAlive(false);    // kill the shell
			isHit = true;
		}
		});

	// Check all player2 tanks
	applyToAllTanks(player2, [&](Tank& t) {
		if (t.Get_has_a_cannon() && sh.GetPos() == t.GetCannonPos() && sh.IsAlive()) {
			t.DestroyCannon();
			sh.SetAlive(false);
			isHit = true;
		}
		});
}



void Game::RestartShells() {
	shells.clear();
}



bool Game::GameEsc(char* keys)
{
	for (int i = 0; i < SIX; i++)
	{
		if (keys[i] == ESC)
			return true;
	}
	return false;
}

bool Game::pause() { // pause the game , wait for a key from user
	Flush(); // cleaning buffer
	char key;
	b.print(Board::Board_Type::PAUSE_BOARD, "");
	while (true) { // until getting a right key
		key = _getch();
		if (key == ESC) {
			return true; // player want to continu play
		}
		else if (key == (int)Board::Board_Type::MAIN_MENU) {
			return false; // player want to return to menu
		}
	}
}


void Game::GameOver(int& winner) //  enter only if has a winner , define the winner DM
{
	if (player1.empty() && player2.empty()) // both loss
	{
		winner_massge = "It's a Tie!!";
		winner = 0;
	}

	else
	{
		if (player2.empty()) // player1 win
		{
			winner_massge = "Player 1 is the Winner!!";
			winner = 1;
		}

		if (player1.empty()) // player2 win
		{
			winner_massge = "Player 2 is the Winner!!";
			winner = 2;
		}
	}
}

void Game::RemoveDeadShells() { //remamber to call after MoveShells
	shells.erase(
		std::remove_if(shells.begin(), shells.end(),
			[](const Shell& shell) { return !shell.IsAlive(); }),
		shells.end()
	);
}

void Game::CheckShellsMovement(Shell& shell, bool& isHit) {
	for (Shell& s : shells) {
		if (&shell != &s) {
			// Skip if it's the same shell (comparing memory addresses) 
			if (shell.isShellCollidingWithShell(s)) {
				shell.SetAlive(false);
				s.SetAlive(false);
				isHit = true;
			}
		}
		ShellCollidingWithTank(shell, isHit);
		ShellCollidingWithWall(shell, isHit);
		ShellCollidingWithCannon(shell, isHit);
	}
}


bool Game::checksAndPreparesGame() {
	// 1. Check if any player has no tanks
	if (player1.empty() || player2.empty())
		return false;

	// 2. Check LEGEND position is valid (inside bounds)
	const int LEGEND_WIDTH = 20;
	const int LEGEND_HEIGHT = 3;

	Point legend_pos = b.getLegendPos();
	int lx = legend_pos.getX();
	int ly = legend_pos.getY();

	if (lx < 0 || ly < 0 || lx + LEGEND_WIDTH > b.MAX_X || ly + LEGEND_HEIGHT > b.MAX_Y)
		return false; // Legend exceeds board bounds

	// 3. Check legend area is empty (i.e., not overlapping with tanks/walls/mines)
	for (int row = 0; row < LEGEND_HEIGHT; row++) {
		for (int col = 0; col < LEGEND_WIDTH; col++) {
			Point temp = { lx + col, ly + row };
			char c = b.getChar(temp);
			if (c != ' ')
				return false;
		}
	}

	return true;
}

void Game::DeleteUnAliveTanks() {
	// --- Player 1 ---
	size_t old_size_p1 = player1.size();

	player1.erase(
		std::remove_if(player1.begin(), player1.end(), [](const Tank& t) {
			return !t.Get_Alive();
			}),
		player1.end()
	);

	if (player1.size() < old_size_p1) {
		if (!player1.empty())
			advanceIndex(index_player1, player1.size());
		else
			index_player1 = 0;
	}

	// --- Player 2 ---
	size_t old_size_p2 = player2.size();

	player2.erase(
		std::remove_if(player2.begin(), player2.end(), [](const Tank& t) {
			return !t.Get_Alive();
			}),
		player2.end()
	);

	if (player2.size() < old_size_p2) {
		if (!player2.empty())
			advanceIndex(index_player2, player2.size());
		else
			index_player2 = 0;
	}
}

void Game::error_board() { // not valid board or no boards
	b.print(Board::Board_Type::ERROR_B, "");
	while (_getch() != (int)Board::Board_Type::MAIN_MENU);
}



int Game::game_mode_board() {
	b.print(Board::Board_Type::GAME_MODE, "");

	int mode = -1;
	char key;

	while (true) {
		key = _getch();


		if (key >= '4' && key <= '6' || key == '2') {
			mode = key - '0';
			break;
		}
	}

	Flush();
	return mode;
}



void Game::assingRandomCannons() {
	if (!player1.empty()) {
		for (Tank& tank : player1) {
			int rand_dir;
			Point cannon_pos;

			do {
				cannon_pos = tank.GetPos();
				rand_dir = std::rand() % 8;
				tank.SetDir((Direction::dir)rand_dir);

				cannon_pos.move(tank.GetDir());
				tank.Set_cannon_pos(cannon_pos);
			} while (b.getChar(cannon_pos) == '#'); //calc again if it is a wall

			cannon_pos.setChar(Direction::directionCannonChars[rand_dir]);
			tank.Set_cannon_pos(cannon_pos);
			tank.Set_cannon_char(Direction::directionCannonChars[rand_dir]);
		}
	}

	if (!player2.empty()) {
		for (Tank& tank : player2) {
			int rand_dir;
			Point cannon_pos;

			do {
				cannon_pos = tank.GetPos();
				rand_dir = std::rand() % 8;
				tank.SetDir((Direction::dir)rand_dir);

				cannon_pos.move(tank.GetDir());
				tank.Set_cannon_pos(cannon_pos);
			} while (b.getChar(cannon_pos) == '#'); //calc again if it is a wall

			cannon_pos.setChar(Direction::directionCannonChars[rand_dir]);
			tank.Set_cannon_pos(cannon_pos);
			tank.Set_cannon_char(Direction::directionCannonChars[rand_dir]);
		}
	}

}

void Game::PrintLegend() {

	const int width = 20;
	const int height = 3;
	Point legendStart = b.getLegendPos();

	int x = legendStart.getX();
	int y = legendStart.getY();

	for (int row = 0; row < height; ++row) {
		Point p = { x, y + row };
		p.gotoxy();

		for (int col = 0; col < width; ++col) {
			// frame
			if (row == 0 || row == height - 1 || col == 0 || col == width - 1)
			{
				std::cout << "+";
				b.currentBoard[row][col] = '+';
			}
			else
				std::cout << " ";
		}
	}

	// print score:
	std::string label = "SCORE:";
	int labelX = x + 2;
	int labelY = y + 1;

	Point labelPos = { labelX, labelY };
	labelPos.gotoxy();
	std::cout << label;

	// save "SCORE:" into currentBoard
	for (int i = 0; i < label.length(); ++i) {
		b.currentBoard[labelY][labelX + i] = label[i];
	}

}


void Game::SetLevel(int level) { // set the level for game start
	b.update_default_pos(); // set all object poses to def
	player1.clear();
	player2.clear();
	b.loadGameBoard(stages[level - 1], player1, player2); // write to the board the char's save all of the tanks positions
}

void Game::updateScoreDisplay() {
	Point legendStart = b.getLegendPos();
	int x = legendStart.getX();
	int y = legendStart.getY();

	Point scorePos = { x + 9, y + 1 };
	scorePos.gotoxy();


	std::cout << "        ";


	scorePos.gotoxy();


	std::cout << winner_score;
}

void Game::set_mode(int choice) {
	switch (choice) {
	case 4:
		isPlayer1Computer = false;
		isPlayer2Computer = false;
		break;
	case 5:
		isPlayer1Computer = true;
		isPlayer2Computer = false;
		break;
	case 6:
		isPlayer1Computer = true;
		isPlayer2Computer = true;
		break;
	}
}


void Game::computerControlTankPlayer1(char* keys,Tank& tank, int& index, const std::vector<Tank>& allies, const std::vector<Tank>& enemies, const std::vector<Shell>& shells) {
	//first handle shells
	for (const Shell& sh : shells) {
		Point shell_check_point = sh.GetPos();
		for (int i = 0; i < FIVE; i++) // for the follwing positions of the tank
		{
			shell_check_point.move(sh.GetDir());
			if (tank.GetPos() == shell_check_point) { //moving the controled tank when a shell is chasing it
				//tank.SetTrankLeft(Tank::TRACK_FORWARD);
				keys[array_index_computer_mode] = 'Q'; array_index_computer_mode++;
				//tank.SetTrankRight(Tank::TRACK_FORWARD);
				keys[array_index_computer_mode] = 'E'; array_index_computer_mode++;
				tank.SetNotStay();
				return;
			}

			for (const Tank& other_allie_tank : allies) {  // change control tank 
				if (&other_allie_tank == &tank) continue;
				if (other_allie_tank.GetPos() == shell_check_point) {
					advanceIndex(index, allies.size());
					return;
				}
			}


		}
	}

	//not shoot if there is an ally in the dir of the cannon
	Point ally_check_point = tank.GetPos();
	ally_check_point.move(tank.GetDir());
	for (int i = 0; i < 20; i++)
	{
		if (b.clashAWeakWall(ally_check_point) || b.clashAWall(ally_check_point))
			break; //uesed to make sure that the loop would not be infinte
		for (const Tank& ally : allies) {
			if (&ally == &tank) continue;
			if (ally_check_point == ally.GetPos() || (ally.Get_has_a_cannon() && ally_check_point == ally.GetCannonPos()))
				return; // beacuse we dont want to shoot in our ally
		}

		ally_check_point.move(tank.GetDir());
	}

	//now it's sure to shoot - we want to shoot if there is an anamy in front of the cannon die

	Point enemy_check_point = tank.GetPos();
	enemy_check_point.move(tank.GetDir());
	for (int i = 0; i < 20; i++)
	{
		if (b.clashAWeakWall(enemy_check_point) || b.clashAWall(enemy_check_point))
			break; //uesed to make sure that the loop would not be infinte
		for (const Tank& enemy : enemies) {
			if (enemy_check_point == enemy.GetPos() || (enemy.Get_has_a_cannon() && enemy_check_point == enemy.GetCannonPos())) {
				if (tank.Get_shooting_cooldown_timer() == 0) {
					//addShell(tank);
					keys[array_index_computer_mode] = 'W'; array_index_computer_mode++;
					return;
				}
			}
		}
		enemy_check_point.move(tank.GetDir());
	}




	// try revers if in front of a wall
	Point forward = tank.GetCannonPos();
	forward.move(tank.GetDir());

	if (b.clashAWall(forward) || b.clashAWeakWall(forward)) {
		//tank.SetTrankLeft(Tank::TRACK_BACKWARD);
		keys[array_index_computer_mode] = 'A'; array_index_computer_mode++;
		//tank.SetTrankRight(Tank::TRACK_BACKWARD);
		keys[array_index_computer_mode] = 'D'; array_index_computer_mode++;
		tank.SetNotStay();
		return;
	}

	//else
	int moveChance = rand() % 6;  // 0–5

	switch (moveChance) {
	case 0:
	case 1:
		tank.SetStay();
		break;
	case 2:
	case 3:
		// forward
		//tank.SetTrankLeft(Tank::TRACK_FORWARD);
		keys[array_index_computer_mode] = 'Q'; array_index_computer_mode++;
		//tank.SetTrankRight(Tank::TRACK_FORWARD);
		keys[array_index_computer_mode] = 'E'; array_index_computer_mode++;
		tank.SetNotStay();
		break;
	case 4:
		// right turn 
		//tank.SetTrankRight(Tank::TRACK_STAYS);
		//keys[array_index_computer_mode] = 'S'; array_index_computer_mode++; // first stay then turn to each dir
		tank.SetNotStay();
		//tank.SetTrankLeft(Tank::TRACK_FORWARD);
		keys[array_index_computer_mode] = 'Q'; array_index_computer_mode++;
		
		break;
	case 5:
		// left turn 
		//tank.SetTrankLeft(Tank::TRACK_STAYS);
		//keys[array_index_computer_mode] = 'S'; array_index_computer_mode++;  // first stay then turn to each dir
		//tank.SetTrankRight(Tank::TRACK_FORWARD);
		tank.SetNotStay();
		keys[array_index_computer_mode] = 'E'; array_index_computer_mode++;
		
		break;
	}

}


void Game::computerControlTankPlayer2(char* keys, Tank& tank, int& index, const std::vector<Tank>& allies, const std::vector<Tank>& enemies, const std::vector<Shell>& shells) {
	//first handle shells
	for (const Shell& sh : shells) {
		Point shell_check_point = sh.GetPos();
		for (int i = 0; i < FIVE; i++) // for the follwing positions of the tank
		{
			shell_check_point.move(sh.GetDir());
			if (tank.GetPos() == shell_check_point) { //moving the controled tank when a shell is chasing it
				//tank.SetTrankLeft(Tank::TRACK_FORWARD);
				keys[array_index_computer_mode] = 'U'; array_index_computer_mode++;
				//tank.SetTrankRight(Tank::TRACK_FORWARD);
				keys[array_index_computer_mode] = 'O'; array_index_computer_mode++;
				tank.SetNotStay();
				return;
			}

			for (const Tank& other_allie_tank : allies) {  // change control tank 
				if (&other_allie_tank == &tank) continue;
				if (other_allie_tank.GetPos() == shell_check_point) {
					advanceIndex(index, allies.size());
					return;
				}
			}


		}
	}

	//not shoot if there is an ally in the dir of the cannon
	Point ally_check_point = tank.GetPos();
	ally_check_point.move(tank.GetDir());
	for (int i = 0; i < 20; i++)
	{
		if (b.clashAWeakWall(ally_check_point) || b.clashAWall(ally_check_point))
			break; //uesed to make sure that the loop would not be infinte
		for (const Tank& ally : allies) {
			if (&ally == &tank) continue;
			if (ally_check_point == ally.GetPos() || (ally.Get_has_a_cannon() && ally_check_point == ally.GetCannonPos()))
				return; // beacuse we dont want to shoot in our ally
		}

		ally_check_point.move(tank.GetDir());
	}

	//now it's sure to shoot - we want to shoot if there is an anamy in front of the cannon die

	Point enemy_check_point = tank.GetPos();
	enemy_check_point.move(tank.GetDir());
	for (int i = 0; i < 20; i++)
	{
		if (b.clashAWeakWall(enemy_check_point) || b.clashAWall(enemy_check_point))
			break; //uesed to make sure that the loop would not be infinte
		for (const Tank& enemy : enemies) {
			if (enemy_check_point == enemy.GetPos() || (enemy.Get_has_a_cannon() && enemy_check_point == enemy.GetCannonPos())) {
				if (tank.Get_shooting_cooldown_timer() == 0) {
					//addShell(tank);
					keys[array_index_computer_mode] = 'I'; array_index_computer_mode++;
					return;
				}
			}
		}
		enemy_check_point.move(tank.GetDir());
	}




	// try revers if in front of a wall
	Point forward = tank.GetCannonPos();
	forward.move(tank.GetDir());

	if (b.clashAWall(forward) || b.clashAWeakWall(forward)) {
		//tank.SetTrankLeft(Tank::TRACK_BACKWARD);
		keys[array_index_computer_mode] = 'J'; array_index_computer_mode++;
		//tank.SetTrankRight(Tank::TRACK_BACKWARD);
		keys[array_index_computer_mode] = 'L'; array_index_computer_mode++;
		tank.SetNotStay();
		return;
	}

	//else
	int moveChance = rand() % 6;  // 0–5

	switch (moveChance) {
	case 0:
	case 1:
		tank.SetStay();
		break;
	case 2:
	case 3:
		// forward
		//tank.SetTrankLeft(Tank::TRACK_FORWARD);
		keys[array_index_computer_mode] = 'U'; array_index_computer_mode++;
		//tank.SetTrankRight(Tank::TRACK_FORWARD);
		keys[array_index_computer_mode] = 'O'; array_index_computer_mode++;
		tank.SetNotStay();
		break;
	case 4:
		// right turn 
		//tank.SetTrankRight(Tank::TRACK_STAYS);
		//keys[array_index_computer_mode] = 'K'; array_index_computer_mode++; // first stay then turn to each dir
		//tank.SetTrankLeft(Tank::TRACK_FORWARD);
		tank.SetNotStay();
		keys[array_index_computer_mode] = 'U'; array_index_computer_mode++;
		
		break;
	case 5:
		// left turn 
		//tank.SetTrankLeft(Tank::TRACK_STAYS);
		//keys[array_index_computer_mode] = 'K'; array_index_computer_mode++;  // first stay then turn to each dir
		//tank.SetTrankRight(Tank::TRACK_FORWARD);
		tank.SetNotStay();
		keys[array_index_computer_mode] = 'O'; array_index_computer_mode++;
		
		break;
	}

}


void Game::HandleComputerPlayers(char* keys) {
	if (isPlayer1Computer && index_player1 < player1.size()) {
		computerControlTankPlayer1(keys,player1[index_player1], index_player1, player1, player2, shells);
	}
	if (isPlayer2Computer && index_player2 < player2.size()) {
		computerControlTankPlayer2 (keys, player2[index_player2], index_player2, player2, player1, shells);
	}
	array_index_computer_mode = 0; //reset
}

void Game::FilterHumanPlayerKeys(const char* keys, char* filteredKeys) {
	for (int i = 0; i < SIX; i++) {
		filteredKeys[i] = '0'; //zero as default

		char k = keys[i];

		// if player1 is computer replace them with zero
		if (!isPlayer1Computer && (k == 'W' || k == 'A' || k == 'S' || k == 'D' || k == 'Q' || k == 'E' || k == 'Z'))
			filteredKeys[i] = k;

		// if player2 is computer replace them with zero
		if (!isPlayer2Computer && (k == 'I' || k == 'J' || k == 'K' || k == 'L' || k == 'U' || k == 'O' || k == 'M'))
			filteredKeys[i] = k;
	}
}






