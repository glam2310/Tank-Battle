#include "GameRegular.h"

void GameRegular::Run(int start_stage)
{
	if (stages.empty())
	{
		error_board();
		return;
	}
	for (int i = start_stage; i <= stages.size(); i++) {
		SetLevel(i);
		assingRandomCannons();
		if (!checksAndPreparesGame()) { // board isnt valid
			continue; // check next stage
		}

		else {
			b.reset();
			b.print(Board::Board_Type::BOARD_GAME, ""); // prints the reset board
			PrintLegend();

			char keys[SIX] = { 0,0,0,0,0,0 };
			int count_game_loop = ZERO;
			while (true)
			{

				if (player1.empty() || player2.empty()) { // If either player has no tanks left, end the game
					int winner;
					GameOver(winner);
					int res = end_level_board();
					if (i != stages.size()) {
						if (res == 1)
							break; // we would like to break this while loop in order to continu next iteretion of the for loop (stages)
						else
							return;
					}
					else
					{
						end_game_board();
						return;
					}
				}
				UpdateShootingCooldowns();
				count_game_loop++;
				if (count_game_loop % 12 == ZERO)
				{
					winner_score -= 25;// score calc by how fast the winner player is winning - so the more time the battel takes the more points the winnwer is lossing!
					updateScoreDisplay();
				}
				HandleComputerPlayers(keys);
				KbhitAndGetch_(keys); // get max of 6 chars from the players
				if (GameEsc(keys))
					if (!pause())
						return;
					else {
						b.print(Board::Board_Type::BOARD_GAME, ""); // prints the curr game board
					}
				char filteredKeys[SIX];
				FilterHumanPlayerKeys(keys, filteredKeys);
				UpdateTrackMovement(keys);
				//player1.draw();
				applyToAllTanks(player1, [](Tank& t) {
					t.draw();
					});

				//player2.draw();
				applyToAllTanks(player2, [](Tank& t) {
					t.draw();
					});

				MoveShells();
				RemoveDeadShells();
				Sleep(250);

				//calc dir for all players
				applyToAllTanks(player1, [&](Tank& t) {
					t.CalcDir(b);
					});
				applyToAllTanks(player2, [&](Tank& t) {
					t.CalcDir(b);
					});


				applyToAllTanks(player1, [&](Tank& t) {
					b.restore(t.GetCannonPos());
					b.restore(t.GetPos());
					});

				applyToAllTanks(player2, [&](Tank& t) {
					b.restore(t.GetCannonPos());
					b.restore(t.GetPos());
					});

				applyToAllTanks(player1, [&](Tank& t) {
					t.MoveTank(b, player1, player2);
					});

				applyToAllTanks(player2, [&](Tank& t) {
					t.MoveTank(b, player1, player2);
					});


				DeleteUnAliveTanks();


			}
		}
	}

}

void GameRegular::main_menu() {
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

