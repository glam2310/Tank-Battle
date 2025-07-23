#pragma once
#include "Game.h"
#include "StepsManager.h"
#include "ResultsManager.h"
#include <vector>

class GameSave : public Game {
private:
    StepsManager stepsManager; 
    ResultsManager resultsMangager;

public:
    GameSave():Game(){}
    void Run(int start_stage) override;
    void GameSave_MoveShells(int iteration);
    void GameSave_CheckShellsMovement(int iteretion, Shell& shell, bool& isHit);
    void  main_menu() override;
};
