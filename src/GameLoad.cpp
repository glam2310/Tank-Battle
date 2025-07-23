#include "GameLoad.h"

void GameLoad::Run(int start_stage)
{
    hideCursor();
    if (stages.empty()) {
        if (!silentMode) error_board();
        return;
    }

    for (int i = start_stage; i <= stages.size(); i++) {
        SetLevel(i);

        std::string screenName = std::to_string(i);
        if (!stepsManager.loadFile(screenName)) {
            clear_board();
            return;
        }

        

        resultsManager.setScreenName(screenName);
        resultsManager.LoadFromFile();

        unsigned int seed = stepsManager.getSeed();
        setSeed(seed);
        assingRandomCannons();

        if (!checksAndPreparesGame()) {
            continue;
        }
        else {
            if (!silentMode) {
                b.reset();
                b.print(Board::Board_Type::BOARD_GAME, "");
                PrintLegend();
            }

            int count_game_loop = 0;
            std::vector<char> keys;

            while (stepsManager.getNextStep(keys)) {
              
                UpdateShootingCooldowns();
                count_game_loop++;
                if (count_game_loop % 12 == 0) {
                    winner_score -= 25;
                    if (!silentMode) updateScoreDisplay();
                }

                // Use loaded keys only
                char filteredKeys[SIX] = { '0', '0','0','0','0','0'};
                char array_keys[SIX];
                for (size_t j = 0; j < keys.size() && j < SIX; ++j)
                {
                    filteredKeys[j] = keys[j];
                    array_keys[j] = keys[j];
                }


                FilterHumanPlayerKeys(array_keys, filteredKeys);
                UpdateTrackMovement(filteredKeys);

                if (!silentMode) {
                    applyToAllTanks(player1, [](Tank& t) { t.draw(); });
                    applyToAllTanks(player2, [](Tank& t) { t.draw(); });
                }

               bool is_shell_not_valid = GameLoad_MoveShells(count_game_loop);
               if (is_shell_not_valid)
                   return;

                if (!silentMode)
                    Sleep(100);

                bool gameValidationFailed = false;

                applyToAllTanks(player1, [&](Tank& t) {
                    t.CalcDir(b);
                    b.restore(t.GetCannonPos());
                    b.restore(t.GetPos());
                    if (t.MoveTank(b, player1, player2)) { //MoveTank return true mean that had at the iteration Mine Death
                        if (!resultsManager.isMineDeathAt(count_game_loop, "P1")) {
                            gameValidationFailed = true;
                        }
                    }
                    });

                applyToAllTanks(player2, [&](Tank& t) {
                    t.CalcDir(b);
                    b.restore(t.GetCannonPos());
                    b.restore(t.GetPos());
                    if (t.MoveTank(b, player1, player2)) {
                        if (!resultsManager.isMineDeathAt(count_game_loop, "P2")) {
                            gameValidationFailed = true;
                        }
                    }
                    });

                // check after the player's tanks moved
                if (gameValidationFailed) {
                    error_resulte("Results file doesn't match Mine Death", count_game_loop);
                    return;
                }

                DeleteUnAliveTanks();
            }

            if (player1.empty() || player2.empty()) {
                int winner;
                GameOver(winner);
                //int res = end_level_board();
            
                int winnerID = player1.empty() ? 2 : 1;
               // resultsManager.setWinnerScore(winnerID, winner_score);


                int expectedWinner = resultsManager.getWinnerID();
                int expectedScore = resultsManager.getWinnerScore();

                if (expectedWinner != winnerID || expectedScore != winner_score)
                {
                    error_resulte("Results file doesn't match finished event!", count_game_loop); 
                    return;
                }


                if (!resultsManager.isFinishedBy(count_game_loop))
                {
                    error_resulte("Game had finish while Results file hadn't!", count_game_loop);
                    return;
                }


                //if (i == stages.size())
                //    return;
            

            }
        }
    }   

    clear_board();
  }

 
bool GameLoad::GameLoad_MoveShells(int iteration) {
    bool hit = false;
    bool error_occur = false;
    bool to_return = false, also_to_return = false;
    for (Shell& shell : shells) {
        b.restoreFromCurrentBoard(shell.GetPos());
        shell.MoveShell();

        if (!silentMode)
        shell.GetPos().draw();

        Point pos = shell.GetPos();
        int x = pos.getX(), y = pos.getY();
        bool isHit = false;
        

        to_return = GameLoad_CheckShellsMovement(iteration, shell, hit);
        if (to_return)
            error_occur = true;

        if (!silentMode)
        Sleep(10);

        b.restoreFromCurrentBoard(shell.GetPos());

        if (!hit) { // another round for the the signal shell
            for (Shell& shell : shells) {
                shell.MoveShell();
                //checks
                if (!silentMode)
                shell.GetPos().draw();

                bool also_to_return = GameLoad_CheckShellsMovement(iteration, shell, hit);
                if (also_to_return)
                    error_occur = true;

                if (!silentMode)
                Sleep(40);

                b.restoreFromCurrentBoard(shell.GetPos());
            }
          
        }
    }
    RemoveDeadShells();
    return error_occur;
}



bool GameLoad::GameLoad_CheckShellsMovement(int iteration, Shell& shell, bool& isHit) {
    bool errorDetected = false; 
     
    for (Shell& s : shells) {
        if (&shell != &s) {
            if (shell.isShellCollidingWithShell(s)) {
                shell.SetAlive(false);
                s.SetAlive(false);
                isHit = true;

                if (!resultsManager.isShellHitAt(iteration, "SHELL", shell.GetPos().getX(), shell.GetPos().getY()) && shell.IsAlive()) {
                   error_resulte("Results file has a shell hit event that didn't happen!", iteration);
                   errorDetected = true;
                }
            }
        } 
        RemoveDeadShells();

        bool is_hit_tank = false, is_hit_wall = false, is_hit_cannon = false;
        ShellCollidingWithTank(shell, is_hit_tank);
        ShellCollidingWithWall(shell, is_hit_wall);
        ShellCollidingWithCannon(shell, is_hit_cannon);

        if (is_hit_tank || is_hit_wall || is_hit_cannon)
            isHit = true;

      

        if (resultsManager.isShellHitAt(iteration, "TANK", shell.GetPos().getX(), shell.GetPos().getY()) != is_hit_tank && shell.IsAlive()) {
            error_resulte("Results file has a shell hit event that didn't happen - tank!", iteration);
            errorDetected = true;
        }

        if (resultsManager.isShellHitAt(iteration, "WALL", shell.GetPos().getX(), shell.GetPos().getY())!= is_hit_wall && shell.IsAlive()) {
            error_resulte("Results file has a shell hit event that didn't happen - wall!", iteration);
            errorDetected = true;
        }

        if (resultsManager.isShellHitAt(iteration, "CANNON", shell.GetPos().getX(), shell.GetPos().getY())!= is_hit_cannon && shell.IsAlive()) {
            error_resulte("Results file has a shell hit event that didn't happen - cannon!", iteration);
            errorDetected = true;
        }

        RemoveDeadShells();
    }
 

    return errorDetected;
}


void GameLoad::error_resulte(string massage, int iteration) {
    b.print(Board::Board_Type::ERROR_RESULTE, massage, iteration);
}

void GameLoad::main_menu() {
    Run(1);
}

void GameLoad::clear_board() {
    b.print(Board::Board_Type::CLEAR_BOARD,"");
    Point start = { 0 ,0 };
    start.gotoxy();
    std::cout << "Run was successful!!!";


}







