#include "Board.h"

const Point Board::DEFAULT_POS = Point(-1, -1);
const Point Board::DEFAULT_LIFE_COUNT_POS = Point(7, 0);
const Point Board::DEFAULT_SCORE_POS = (8, 1);


void Board::reset() { // reset the curr board to wanted original board
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], original_board[i], MAX_X + 1);
	}
}

void Board::print(Board_Type Board, string message, int score) { // here score is points or the num of iterations
	const char** board_to_print = nullptr;
	Point start_print = { 0,0 };
	start_print.gotoxy();
	bool _message = false;

	switch (Board) // checks the right board
	{
	case Board_Type::MAIN_MENU:
		board_to_print = menu_board;
		break;
	case Board_Type::BOARD_GAME:
		//board_to_print = original_board;
		for (int i = 0; i < MAX_Y - 1; i++) {
			std::cout << original_board[i] << '\n';
		}
		break;
	case Board_Type::STAGES:
		//board_to_print = stages_board;
		for (int i = 0; i < MAX_Y - 1; i++) {
			std::cout << stages_board[i] << '\n';
		}
		break;
	case Board_Type::INSTRUCTIONS:
		board_to_print = instructions_board;
		break;
	case Board_Type::END_OF_GAME:
		board_to_print = end_of_game_board;
		_message = true;
		break;
	case Board_Type::END_OF_LEVEL:
		board_to_print = end_of_level_board;
		_message = true;
		break;
	case Board_Type::PAUSE_BOARD:
		board_to_print = pause_board;
		break;
	case Board_Type::ERROR_B:
		board_to_print = error_board;
		break;
	case Board_Type::GAME_MODE:
		board_to_print = game_mode_board;
		break;
	case Board_Type::ERROR_RESULTE:
		board_to_print = error_resulte;
		_message = true;
		break;
	case Board_Type::CLEAR_BOARD:
		board_to_print = clear_board;
		break;
	}
	if (Board != Board_Type::BOARD_GAME && (Board != Board_Type::STAGES)) {

		for (int i = 0; i <= MAX_Y - 1; i++) { // we coverd all cases so for sure we wont get a non valod pointer
			std::cout << board_to_print[i] << '\n';
		}
		//std::cout << board_to_print[MAX_Y - 1];
	}

	if (Board == Board_Type::ERROR_RESULTE && !message.empty())
	{

		Point maddagePoint = { 0, 7 };
		maddagePoint.gotoxy();
		std::cout << "*";
		int innerWidth = MAX_X - 2; // Width between the asterisks
		std::string IterationMsg = "Iteration: " + std::to_string(score) + " | " + message;
		int scoreLength = IterationMsg.length();
		int leftPaddingScore = (innerWidth - scoreLength) / 2;
		int rightPaddingScore = innerWidth - scoreLength - leftPaddingScore;
		for (int i = 0; i < leftPaddingScore; i++) std::cout << " ";
		std::cout << IterationMsg;
		for (int i = 0; i < rightPaddingScore; i++) std::cout << " ";
		std::cout << "*";
	}

	// If it's the end game screen, display the centered message
	if ((Board == Board_Type::END_OF_GAME || Board == Board_Type::END_OF_LEVEL) && !message.empty()) {
		// Position cursor at row 3
		Point messagePoint = { 0, 3 };
		messagePoint.gotoxy();

		// Print the message line with asterisks at the edges
		std::cout << "*";

		// Calculate center position for the message
		int innerWidth = MAX_X - 2; // Width between the asterisks
		int messageLength = message.length();
		int leftPadding = (innerWidth - messageLength) / 2;
		int rightPadding = innerWidth - messageLength - leftPadding;

		// Print spaces before the message
		for (int i = 0; i < leftPadding; i++) {
			std::cout << " ";
		}

		// Print the message
		std::cout << message;

		// Print spaces after the message
		for (int i = 0; i < rightPadding; i++) {
			std::cout << " ";
		}

		// Print the closing asterisk
		std::cout << "*";


		Point scorePoint = { 0, 13 };
		scorePoint.gotoxy();
		std::cout << "*";
		std::string scoreMsg = "WINNER SCORE: " + std::to_string(score);
		int scoreLength = scoreMsg.length();
		int leftPaddingScore = (innerWidth - scoreLength) / 2;
		int rightPaddingScore = innerWidth - scoreLength - leftPaddingScore;
		for (int i = 0; i < leftPaddingScore; i++) std::cout << " ";
		std::cout << scoreMsg;
		for (int i = 0; i < rightPaddingScore; i++) std::cout << " ";
		std::cout << "*";

	}



}

bool Board::clashAWall(Point p)
{
	if (Board::getCharFromCurrentBoard(p) == wall_ch)
		return true;
	else return false;
}

bool Board::clashAWeakWall(Point p)
{
	if (Board::getCharFromCurrentBoard(p) == weakened_wall_ch)
		return true;
	else return false;
}

void Board::update_default_pos() {
	Point LIFE_COUNT_POS = DEFAULT_LIFE_COUNT_POS; // point for the life count place according to legend board
	Point SCORE_POS = DEFAULT_SCORE_POS; // point for the score according to legend board
}

/*
bool Board::checkCharFromBoard explain:
we track the players tanks positions using a std::vector<Tank>.
we do NOT keep their characters ('O', etc.) in originalBoard.
Instead - Store their positions,Replace their character with ' ' in the board after loading,
and Draw them dynamically during the game loop. */

bool Board::checkCharFromBoard(char c, int pos_x, int pos_y, std::vector<Tank>& player1, std::vector<Tank>& player2) {
	if (c == player1_tank_marker) {
		// adding tank to player1 team
		player1.push_back(Tank(Point(pos_x, pos_y)));


		original_board[pos_y][pos_x] = empty_ch;

		return true;
	}
	else if (c == player2_tank_marker) {
		// adding tank to player2 team

		player2.push_back(Tank(Point(pos_x, pos_y)));


		original_board[pos_y][pos_x] = empty_ch;

		return true;
	}
	else if (c == 'L')
	{
		Legend_pos = Point(pos_x, pos_y);
		original_board[pos_y][pos_x] = empty_ch;
		return true;
	}

	return false;
}

void Board::fillStageMenuBoard(std::vector <string>& stages) { //change the board according to "dynamic list" of stages.
	int row = 10; // where the "dynamic" list begins

	for (size_t i = 0; i < stages.size() && row < MAX_Y - 1; ++i, ++row) {
		// Clear the content area between borders
		for (int j = 1; j < MAX_X - 1; ++j) {
			stages_board[row][j] = ' ';
		}

		// Create line: (1) StageName
		std::string entry = "(" + std::to_string(i + 1) + ") " + stages[i];
		int col = 10; // left padding inside border

		for (size_t j = 0; j < entry.size() && col + j < MAX_X - 1; ++j) {
			stages_board[row][col + j] = entry[j];
		}
	}
}
/* void Board::loadGameBoard:
Purpose of the Function
-Open a text file that represents a game board.
-For each character:
Store it in original_board.
If it's a special character ('1', '2'), handle it accordingly (in checkCharFromBoard()). */

void Board::loadGameBoard(const std::string& f_name, std::vector<Tank>& player1, std::vector<Tank>& player2) {
	int curr_row = 0;
	int curr_col;
	char c;
	std::ifstream board1(f_name); //open the file 
	if (!board1.is_open()) { // if open dosen't succeeded  - print error message
		std::cerr << "Error: Unable to open file " << f_name << std::endl;
		return;
	}
	while (curr_row < MAX_Y && !board1.eof()) { //read the file
		curr_col = 0; //Resetting the column counter on each new row
		while (curr_col < MAX_X && board1.get(c) && c != '\n') { // read file until end of line or reach to MAX X
			if (!checkCharFromBoard(c, curr_col, curr_row, player1, player2))
				original_board[curr_row][curr_col] = c;
			curr_col++;
		}

		while (c != '\n' && board1.get(c)); // get chars after max_x 
		curr_row++;
	}
	board1.close();
}










