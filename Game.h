#include "Tank.h"
#include <conio.h>
#include "Board.h"
#include "shell.h"
#include <vector>
#include <functional>


using std::string;

#pragma once
class Game
{
protected:
	std::vector <Tank> player1{}; // vector of all the tank objects of player1
	std::vector <Tank> player2{}; // vector of all the tank objects of player2
	string winner_massge; // messsge that will seen at screen at the end of the game
	Board b;
	std::vector<Shell> shells; // vector of all shells in the game
	std::vector<std::string> stages; // vector of all the name files
	int index_player1 = 0; // index of controlled tank among player1 tanks
	int index_player2 = 0; // index of controlled tank among player2 tanks
	int winner_score = 10000; // stating score of each level
	unsigned int seed;
	bool isPlayer1Computer = false; // computer mode or human
	bool isPlayer2Computer = false; // computer mode or human
	int array_index_computer_mode = 0;


	void HelperUpdateTrackMovement(char ch);


	static constexpr int ESC = 27;
	static constexpr char PLAY = '1';
	static constexpr char BACK_TO_MENU = '2';
	static constexpr char INSTRUCTIONS = '8';
	static constexpr char SCREENS = '3';
	static constexpr char EXIT = '9';
	static const Point default_player1;
	static const Point default_player2;

	void ShellCollidingWithTank(Shell& sh, bool& isHit);
	void ShellCollidingWithWall(Shell& sh, bool& isHit);
	void ShellCollidingWithCannon(Shell& sh, bool& isHit);
	void RestartShells();

	void applyToAllTanks(std::vector<Tank>& tanks, const std::function<void(Tank&)>& action) { //// Apply a function to all tanks in player1's / player2's vector.
		for (Tank& tank : tanks) {
			action(tank);
		}
	}

public:
	Game() { //ctor
		getAllFileNames(stages, ".screen"); // get all boards files names before game started
		seed = static_cast<unsigned int>(time(nullptr)); //seed
		std::srand(seed);
	};

	virtual ~Game() = default;

	virtual void Run(int start_stage) = 0; // run the game (game loop)
	void KbhitAndGetch_(char* keys);
	void UpdateTrackMovement(char* keys);
	virtual void main_menu() = 0; // func for managing menu
	void restart_game(); // reset game before players wants to play again 
	void instructions_menu();
	int stages_menu();
	bool GameEsc(char* keys);
	bool pause();
	void GameOver(int& winner); //  //  enter only if has a winner , define the winner DM( and brake out the Run func and print the end_of_game_board)
	void end_game_board();
	int end_level_board();
	void addShell(Tank& player); // make new shell and adding to the shells vector
	void UpdateShootingCooldowns();
	void MoveShells();
	void RemoveDeadShells();
	void CheckShellsMovement(Shell& shell, bool& isHit);
	//bool CheckNoOverrideTank();
	void SetLevel(int level);
	bool checksAndPreparesGame();
	void DeleteUnAliveTanks();
	void error_board();
	int game_mode_board();
	void assingRandomCannons();
	void PrintLegend();
	void updateScoreDisplay();
	void set_mode(int choice); // this func set the player mode (computer / human) by the user input
	void computerControlTankPlayer1(char* keys, Tank& tank, int& index, const std::vector<Tank>& allies, const std::vector<Tank>& enemies, const std::vector<Shell>& shells);
	void computerControlTankPlayer2(char* keys, Tank& tank, int& index, const std::vector<Tank>& allies, const std::vector<Tank>& enemies, const std::vector<Shell>& shells);
	void HandleComputerPlayers(char* keys);
	void FilterHumanPlayerKeys(const char* keys, char* filteredKeys);

	unsigned int getSeed() const { return seed; }
	void setSeed(unsigned int s) { seed = s; std::srand(seed); } 


};

