#include "GameSave.h"

void GameSave::Run(int start_stage)
{
    if (stages.empty()) {
        error_board();
        return;
    }

   // seed is for the whole game
    unsigned int fixedSeed = (unsigned int)time(NULL);
    setSeed(fixedSeed); //srand

    for (int i = start_stage; i <= stages.size(); i++) {
        SetLevel(i);
        stepsManager.resetTime();
        resultsMangager.reset();
        stepsManager.resetAll();
        shells.clear();
        

        // Open steps file for saving game steps
        std::string screenName = std::to_string(i);
        if (!stepsManager.openFile(screenName)) {
            error_board();
            return;
        }

        resultsMangager.setScreenName(std::to_string(i));

        // Save the seed so random cannon placement can be reproduced
        stepsManager.setSeed(fixedSeed); // update the seed at the steps manager

        setSeed(fixedSeed);
        assingRandomCannons();

        if (!checksAndPreparesGame()) {
            continue;
        }
        else {
            b.reset();
            b.print(Board::Board_Type::BOARD_GAME, "");
            PrintLegend();

            char keys[SIX] = {'0','0','0','0','0','0'};
            int count_game_loop = 0;

            while (true) {
                if (player1.empty() || player2.empty()) {
                    int winner;
                    GameOver(winner);
                    int res = end_level_board();
                    resultsMangager.setWinnerScore(winner, winner_score); // Save winner data
                    resultsMangager.SaveToFile(); // Save result file

                    // Close steps file at the end of the level
                    stepsManager.closeFile();

                    if (i != stages.size()) {
                        if (res == 1)
                            break;
                        else
                            return;
                    }
                    else {
                        end_game_board();
                        return;
                    }
                }

                UpdateShootingCooldowns();
                count_game_loop++;
                if (count_game_loop % 12 == 0) {
                    winner_score -= 25;
                    updateScoreDisplay();
                }

                HandleComputerPlayers(keys);

                KbhitAndGetch_(keys);

                // Convert raw key input to a vector and save it with current time step
                std::vector<char> pressedKeys;
                for (int j = 0; j < SIX; ++j) {
                    //if (keys[j] != 0)
                        pressedKeys.push_back(keys[j]);
                }
                stepsManager.recordStep(pressedKeys);
                stepsManager.incrementTime();

                if (GameEsc(keys)) {
                    if (!pause()) {
                        stepsManager.closeFile();
                        return;
                    }
                    else {
                        b.print(Board::Board_Type::BOARD_GAME, "");
                    }
                }

                char filteredKeys[SIX];
                FilterHumanPlayerKeys(keys, filteredKeys);
                UpdateTrackMovement(keys);

                applyToAllTanks(player1, [](Tank& t) { t.draw(); });
                applyToAllTanks(player2, [](Tank& t) { t.draw(); });

                GameSave_MoveShells(count_game_loop);
                RemoveDeadShells();
                Sleep(250);


                applyToAllTanks(player1, [&](Tank& t) {
                    t.CalcDir(b);
                    b.restore(t.GetCannonPos());
                    b.restore(t.GetPos());
                    if (t.MoveTank(b, player1, player2))
                    {
                        resultsMangager.addMineDeath(count_game_loop, "P1"); // the dead tank is belong to P1 = player1 
                    }
                    });

                applyToAllTanks(player2, [&](Tank& t) {
                    t.CalcDir(b);
                    b.restore(t.GetCannonPos());
                    b.restore(t.GetPos());
                    if (t.MoveTank(b, player1, player2))
                    {
                        resultsMangager.addMineDeath(count_game_loop, "P2"); //  the dead tank is belong to P2 = player2
                    }
                    });



                DeleteUnAliveTanks();
            }
        }
    }
}



void GameSave::GameSave_MoveShells(int iteration) {
 

    for (Shell& shell : shells) {
        bool hit = false;
        b.restoreFromCurrentBoard(shell.GetPos());
        shell.MoveShell();
        shell.GetPos().draw();

        GameSave_CheckShellsMovement(iteration, shell, hit);

        Sleep(70);
        b.restoreFromCurrentBoard(shell.GetPos());

        if (!hit) { // another round for the signal shell
            for (Shell& shell : shells) {
                shell.MoveShell();
                shell.GetPos().draw();

                GameSave_CheckShellsMovement(iteration, shell, hit);

                Sleep(70);
                b.restoreFromCurrentBoard(shell.GetPos());
            }
        }
    }

    RemoveDeadShells(); 
}


void GameSave::GameSave_CheckShellsMovement(int iteretion, Shell& shell, bool& isHit) {
    for (Shell& s : shells) {
        if (&shell != &s) {
            // Skip if it's the same shell (comparing memory addresses) 
            if (shell.isShellCollidingWithShell(s)) {
                shell.SetAlive(false);
                s.SetAlive(false);
                isHit = true;
                resultsMangager.addShellHit(iteretion, "SHELL", shell.GetPos().getX(), shell.GetPos().getY());
            }
        }
        bool is_hit_tank = false, is_hit_wall = false, is_hit_cannon = false;
        ShellCollidingWithTank(shell, is_hit_tank);
        ShellCollidingWithWall(shell, is_hit_wall);
        ShellCollidingWithCannon(shell, is_hit_cannon);

        if (is_hit_tank || is_hit_wall || is_hit_cannon)
            isHit = true;

        if (is_hit_tank) {
            resultsMangager.addShellHit(iteretion, "TANK", shell.GetPos().getX(), shell.GetPos().getY());
        }
        if (is_hit_wall) {
            resultsMangager.addShellHit(iteretion, "WALL", shell.GetPos().getX(), shell.GetPos().getY());
        }
        if (is_hit_cannon) {
            resultsMangager.addShellHit(iteretion, "CANNON", shell.GetPos().getX(), shell.GetPos().getY());
        }
    }
}

void GameSave::main_menu() {
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


