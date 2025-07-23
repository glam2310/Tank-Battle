#pragma once
#include "Game.h"
#include "StepsManager.h"
#include "ResultsManager.h"
#include <set>


class GameLoad : public Game {
private:
    StepsManager stepsManager;
    ResultsManager resultsManager;
    bool silentMode;
  

public:
    GameLoad(bool silent = false) : Game(), silentMode(silent) {}
    void Run(int start_stage) override;
    bool GameLoad_MoveShells(int iteration);
    bool GameLoad_CheckShellsMovement(int iteretion, Shell& shell, bool& isHit); // return true if a shell hit someting and it is not corresponding with the resualte file
    void error_resulte(string massage, int iteration);  // Result error reporting
    void main_menu() override;
    void clear_board();


};
