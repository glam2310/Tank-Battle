#pragma once
#include <string>
#include <fstream>
#include "Point.h"
#include "Tank.h"
#include "Utils.h"

using std::string;

class Board
{
public:
	const enum Boardsize { MAX_X = 80, MAX_Y = 25 }; // const board size
	//const Point PRINT_START_POINT = { 3, 31 };

private:
	static const Point DEFAULT_POS;
	static const Point DEFAULT_LIFE_COUNT_POS;
	static const Point DEFAULT_SCORE_POS;
	Point Legend_pos = { -1,-1 };
	/*
	const char* original_board[MAX_Y] = {
		//  01234567890123456789012345678901234567890123456789012345678901234567890123456789
		   "                                                                                ", // 0
		   "                                                                                ", // 1
		   "    ####################         ################         ################      ", // 2
		   "    #                            #                        #                     ", // 3
		   "    #                            #                        #       @             ", // 4
		   "    #                            #              ###########                     ", // 5
		   "    #                            #                        ################      ", // 6
		   "                                 #                                              ", // 7
		   "                                 #                                              ", // 8
		   "    #####                                                            #####      ", // 9
		   "    #                                                                #          ", // 10
		   "    #         @                                                      #          ", // 11
		   "    #                                                                #          ", // 12
		   "    #                                                                #          ", // 13
		   "    #             ###############################                    #          ", // 14
		   "    #                                           #                    #          ", // 15
		   "    #                                  @        #                    #          ", // 16
		   "    #                                           #                    #          ", // 17
		   "                                                                     #          ", // 18
		   "                                                                                ", // 19
		   "                                                              @                 ", // 20
		   "                                                                                ", // 21
		   "                    ################                                            ", // 22
		   "        @                                                                       ", // 23
		   "                                                                                "  // 24
	};
	*/

	char original_board[MAX_Y][MAX_X + 1]; // +1 for "\0"	

	char stages_board[MAX_Y][MAX_X + 1] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************", // 0
		  "*                                                                              *", // 1
		  "*                                                                              *", // 2
		  "*                               TANK BATTLE STAGES                             *", // 3
		  "*                                 PICK YOUR LEVEL                              *", // 4
		  "*                                                                              *", // 5
		  "********************************************************************************", // 6
		  "*                                                                              *", // 7
		  "*                            (0) Return to the Main Menu                       *", // 8
		  "*                                                                              *", // 9
		  "*                                                                              *", // 10
		  "*                                                                              *", // 11
		  "*                                                                              *", // 12
		  "*                                                                              *", // 13
		  "*                                                                              *", // 14
		  "*                                                                              *", // 15
		  "*                                                                              *", // 16
		  "*                                                                              *", // 17
		  "*                                                                              *", // 18
		  "*                                                                              *", // 19
		  "*                                                                              *", // 20
		  "*                                                                              *", // 21
		  "*                                                                              *", // 22
		  "*                                                                              *", // 23
		  "********************************************************************************"  // 24
	};

	const char* menu_board[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************", // 0
		  "*                                                                              *", // 1
		  "*                                                                              *", // 2
		  "*                               TANK BATTLE GAME                               *", // 3
		  "*                                                                              *", // 4
		  "*                                                                              *", // 5
		  "********************************************************************************", // 6
		  "*                                                                              *", // 7
		  "*                                                                              *", // 8
		  "*                                                                              *", // 9
		  "*                                                                              *", // 10
		  "*                       MAIN MENU :                                            *", // 11
		  "*                      ¯¯¯¯¯¯¯¯¯¯¯¯¯                                           *", // 12
		  "*                       (1) Start New Game                                     *", // 13
		  "*                       (8) Present Instructions and Keys                      *", // 14
		  "*                       (3) Pick stage to begin with                           *", // 15
		  "*                       (9) EXIT                                               *", // 16
		  "*                                                                              *", // 17
		  "*                                                                              *", // 18
		  "*                                                                              *", // 19
		  "*                                                                              *", // 20
		  "*                                                                              *", // 21
		  "*                                                                              *", // 22
		  "*                                                                              *", // 23
		  "********************************************************************************"  // 24
	};

	const char* game_mode_board[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************", // 0
		  "*                                                                              *", // 1
		  "*                                                                              *", // 2
		  "*                               TANK BATTLE GAME                               *", // 3
		  "*                                                                              *", // 4
		  "*                                                                              *", // 5
		  "********************************************************************************", // 6
		  "*                                                                              *", // 7
		  "*                                                                              *", // 8
		  "*                                                                              *", // 9
		  "*                                                                              *", // 10
		  "*                       CHOOSE MODE GAME:                                      *", // 11
		  "*                       ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯                                     *", // 12
		  "*                       (4) Human vs. Human                                    *", // 13
		  "*                       (5) Human vs. Computer                                 *", // 14
		  "*                       (6) Computer vs. Computer                              *", // 15
		  "*                                                                              *", // 16
		  "*                                                                              *", // 17
		  "*                                                                              *", // 18
		  "*                                                                              *", // 19
		  "*                       Press (2) to return to the main menu.                  *", // 20
		  "*                                                                              *", // 21
		  "*                                                                              *", // 22
		  "*                                                                              *", // 23
		  "********************************************************************************"  // 24
	};

	const char* error_board[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************", // 0
		  "*                                                                              *", // 1
		  "*                                                                              *", // 2
		  "*                               BOARD ERROR                                    *", // 3
		  "*                                                                              *", // 4
		  "*                                                                              *", // 5
		  "********************************************************************************", // 6
		  "*                                                                              *", // 7
		  "*                                                                              *", // 8
		  "*             The selected board is invalid or no boards are available.        *", // 9
		  "*                                                                              *", // 10
		  "*                                                                              *", // 11
		  "*                Please check your board files and try again.                  *", // 12
		  "*                                                                              *", // 13
		  "********************************************************************************", // 14
		  "*                                                                              *", // 15
		  "*                                                                              *", // 16
		  "*                                                                              *", // 17
		  "*                      Press (2) to return to the main menu.                   *", // 18
		  "*                                                                              *", // 19
		  "*                                                                              *", // 20
		  "*                                                                              *", // 21
		  "*                                                                              *", // 22
		  "*                                                                              *", // 23
		  "********************************************************************************"  // 24
	};

	const char* instructions_board[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************", // 0
		  "*                          TANK BATTLE - INSTRUCTIONS                          *", // 1
		  "*                        Press (2) to return to main menu                      *", // 2
		  "********************************************************************************", // 3
		  "* KEYS:                           | GAME ELEMENTS:                             *", // 4
		  "* ¯¯¯¯¯                           | ¯¯¯¯¯¯¯¯¯¯¯¯¯¯                             *", // 5
		  "* PLAYER 1:        PLAYER 2:      | Tank        : O     | Wall       : #       *", // 6
		  "* RIGHT fwd: E     RIGHT fwd: O   | Cannon (U/D): |     | Mine       : @       *", // 7
		  "* RIGHT bck: D     RIGHT bck: L   | Cannon (L/R): -     | Tank Shell : *       *", // 8
		  "* LEFT fwd : Q     LEFT fwd : U   | Cannon (DIAG): /    |                      *", // 9
		  "* LEFT bck : A     LEFT bck : J   |                                            *", // 10
		  "* STAY     : S     STAY     : K   | MOVEMENT:                                  *", // 11
		  "* SHOOT    : W     SHOOT    : I   | ¯¯¯¯¯¯¯¯¯                                  *", // 12
		  "* SWITCH   : Z     SWITCH   : M   | Both tracks same direction: move straight  *", // 13
		  "*                                 | One track only: rotate in place (8 steps)  *", // 14
		  "* OBJECTIVE:                      | Opposite tracks: rotate quickly (4 steps)  *", // 15
		  "* ¯¯¯¯¯¯¯¯¯¯                      |                                            *", // 16
		  "* Defeat enemy tanks by hitting them with shells or leading them to mines.     *", // 17
		  "* Avoid enemy fire and mines yourself. Board edges act as tunnels to the       *", // 18
		  "* opposite side. Shells destroy walls after two hits.                          *", // 19
		  "*                                                                              *", // 20
		  "* After shooting, tanks cannot shoot again for 5 game cycles.                  *", // 21
		  "*                                                                              *", // 22
		  "* PAUSE: Press ESC to pause. Press ESC again to resume or X to return to menu. *", // 23
		  "********************************************************************************"  // 24
	};


	const char* end_of_game_board[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************", //0
		  "*                                                                              *", //1
		  "*                                  Game Over!                                  *", //2
		  "*                                                                              *", //3
		  "********************************************************************************", //4
		  "*                                                                              *", //5
		  "*                        ############################                          *", //6
		  "*                        #                          #                          *", //7
		  "*                        #         Good job!        #                          *", //8
		  "*                        #  You've reached the end  #                          *", //9
		  "*                        #       of the Game!       #                          *", //10
		  "*                        #                          #                          *", //11
		  "*                        ############################                          *", //12
		  "*                                                                              *", //13
		  "*                                                                              *", //14
		  "*          #########################################################           *", //15
		  "*          #                                                       #           *", //16
		  "*          #           Press (2) to Return to the Main Menu        #           *", //17
		  "*          #                                                       #           *", //18
		  "*          #########################################################           *", //19
		  "*                                                                              *", //20
		  "*                             SEE YOU NEXT TIME!                               *", //21
		  "*                                                                              *", //22
		  "*                                                                              *", //23
		  "********************************************************************************"  //24
	};

	const char* end_of_level_board[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************", //0
		  "*                                                                              *", //1
		  "*                                  Game Over!                                  *", //2
		  "*                                                                              *", //3
		  "********************************************************************************", //4
		  "*                                                                              *", //5
		  "*                        ############################                          *", //6
		  "*                        #                          #                          *", //7
		  "*                        #         Good job!        #                          *", //8
		  "*                        #  You've reached the end  #                          *", //9
		  "*                        #       of the Game!       #                          *", //10
		  "*                        #                          #                          *", //11
		  "*                        ############################                          *", //12
		  "*                                                                              *", //13
		  "*                                                                              *", //14
		  "*          #########################################################           *", //15
		  "*          #                                                       #           *", //16
		  "*          #           Press (2) to Return to the Main Menu        #           *", //17
		  "*          #           Press (1) to next level                     #           *", //18
		  "*          #########################################################           *", //19
		  "*                                                                              *", //20
		  "*                             SEE YOU NEXT TIME!                               *", //21
		  "*                                                                              *", //22
		  "*                                                                              *", //23
		  "********************************************************************************"  //24
	};


	const char* pause_board[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************", // 0
		  "*                                                                              *", // 1
		  "*                                                                              *", // 2
		  "*                               GAME PAUSED                                    *", // 3
		  "*                                                                              *", // 4
		  "*                                                                              *", // 5
		  "********************************************************************************", // 6
		  "*                                                                              *", // 7
		  "*                                                                              *", // 8
		  "*                         The game is currently paused.                        *", // 9
		  "*                         Take a deep breath...                                *", // 10
		  "*                                                                              *", // 11
		  "*                                                                              *", // 12
		  "*                                                                              *", // 13
		  "********************************************************************************", // 14
		  "*                                                                              *", // 15
		  "*                                                                              *", // 16
		  "*                                                                              *", // 17
		  "*                      Press (ESC) to continue playing,                        *", // 18
		  "*                   or (2) to end the game and return to the main menu.        *", // 19
		  "*                                                                              *", // 20
		  "*                                                                              *", // 21
		  "*                                                                              *", // 22
		  "*                                                                              *", // 23
		  "********************************************************************************"  // 24
	};


	const char* error_resulte[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************", // 0
		  "*                                                                              *", // 1
		  "*                                                                              *", // 2
		  "*                             Result error reporting!                          *", // 3
		  "*                                                                              *", // 4
		  "*                                                                              *", // 5
		  "********************************************************************************", // 6
		  "*                                                                              *", // 7
		  "*                                                                              *", // 8
		  "*                                                                              *", // 9
		  "*                                                                              *", // 10
		  "*                                                                              *", // 11
		  "*                                                                              *", // 12
		  "*                                                                              *", // 13
		  "********************************************************************************", // 14
		  "*                                                                              *", // 15
		  "*                                                                              *", // 16
		  "*                                                                              *", // 17
		  "*                                                                              *", // 18
		  "*                                                                              *", // 19
		  "*                                                                              *", // 20
		  "*                                                                              *", // 21
		  "*                                                                              *", // 22
		  "*                                                                              *", // 23
		  "********************************************************************************"  // 24
	};

	const char* clear_board[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************", // 0
		  "*                                                                              *", // 1
		  "*                                                                              *", // 2
		  "*                                                                              *", // 3
		  "*                                                                              *", // 4
		  "*                                                                              *", // 5
		  "*                                                                              *", // 6
		  "*                                                                              *", // 7
		  "*                                                                              *", // 8
		  "*                                                                              *", // 9
		  "*                                                                              *", // 10
		  "*                                                                              *", // 11
		  "*                                                                              *", // 12
		  "*                                                                              *", // 13
		  "*                                                                              *", // 14
		  "*                                                                              *", // 15
		  "*                                                                              *", // 16
		  "*                                                                              *", // 17
		  "*                                                                              *", // 18
		  "*                                                                              *", // 19
		  "*                                                                              *", // 20
		  "*                                                                              *", // 21
		  "*                                                                              *", // 22
		  "*                                                                              *", // 23
		  "********************************************************************************"  // 24
	};

public:
	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for "\0" 
	const enum class Board_Type { GAME_MODE = '0', BOARD_GAME = '1', MAIN_MENU = '2', END_OF_GAME = '4', INSTRUCTIONS = '8', PAUSE_BOARD = '5', STAGES = '6', END_OF_LEVEL = '7', ERROR_B = '9' , ERROR_RESULTE , CLEAR_BOARD }; // const board type

	/*
	inline bool operator!=(char ch, Board_Type board_ch) {
			return ch != static_cast<char>(board_ch);
		}
		inline bool operator==(char ch, Board_Type board_ch) {
			return ch == static_cast<char>(board_ch);
		}
	*/

	// Game character constants
	static constexpr char legend_ch = 'L';       // Legend marker
	static constexpr char tank_body_ch = 'O';    // Tank body
	static constexpr char cannon_up_down_ch = '|'; // Cannon pointing up or down
	static constexpr char cannon_left_right_ch = '-'; // Cannon pointing left or right
	static constexpr char cannon_up_right_ch = '/'; // Cannon pointing diagonally up-right
	static constexpr char cannon_up_left_ch = '\\'; // Cannon pointing diagonally up-left / down -right
	static constexpr char cannon_down_left_ch = '/'; // Cannon pointing diagonally down-left
	static constexpr char wall_ch = '#';         // Wall
	static constexpr char mine_ch = '@';         // Mine
	static constexpr char shell_ch = '*';        // Tank shell/projectile
	static constexpr char player1_tank_marker = '1'; // Marker for player 1 tank in screen file
	static constexpr char player2_tank_marker = '2'; // Marker for player 2 tank in screen file
	static constexpr char weakened_wall_ch = '='; // Wall that's been hit once (optional)
	static constexpr char empty_ch = ' ';


	Point LIFE_COUNT_POS = DEFAULT_LIFE_COUNT_POS; // point for the life count place according to legend board
	Point SCORE_POS = DEFAULT_SCORE_POS; // point for the score according to legend board


	Board() {
		for (size_t col = 0; col < MAX_X; col++)
			for (size_t row = 0; row < MAX_Y; row++)
			{
				currentBoard[row][col] = empty_ch;
				original_board[row][col] = empty_ch;
			}

	}
	void reset();
	void print(Board_Type Board, string message, int score = 0);
	char getChar(Point p) const { // returns the char on original board that at the point
		return original_board[p.getY()][p.getX()];
	}
	char getCharFromCurrentBoard(Point p) const { // returns the char on curr board that at the point
		return currentBoard[p.getY()][p.getX()];
	}
	void restore(Point p) { // get back the char from original board to the curr board at point
		char c = getCharFromCurrentBoard(p);
		p.draw(c);
	}
	void restoreFromCurrentBoard(Point p) { // get back the char from original board to the curr board at point
		char c = getCharFromCurrentBoard(p);
		p.draw(c);
	}

	bool clashAWall(Point p);

	//void PrepareAnEndGameBoard(char updated_board[MAX_Y][MAX_X], string winner_message);

	bool clashAWeakWall(Point p);
	void WeakenWall(Point p) {
		p.draw(weakened_wall_ch);
		currentBoard[p.getY()][p.getX()] = weakened_wall_ch;
	}
	void DeleteWeakWall(Point p) {
		p.draw(' ');
		currentBoard[p.getY()][p.getX()] = empty_ch;
	}

	void update_default_pos();


	void loadGameBoard(const std::string& f_name, std::vector <Tank>& player1, std::vector <Tank>& player2);
	bool checkCharFromBoard(char c, int pos_x, int pos_y, std::vector <Tank>& player1, std::vector <Tank>& player2); // helper to func - loadGameBoard 
	void fillStageMenuBoard(std::vector <string>& stages);
	inline Point getLegendPos() {
		return Legend_pos;
	}
};

