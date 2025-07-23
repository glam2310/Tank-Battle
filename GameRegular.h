#pragma once
#include "Game.h"

class GameRegular : public Game {
public:
    GameRegular() :Game() {};
    void Run(int start_stage) override;
    void  main_menu() override;
};
