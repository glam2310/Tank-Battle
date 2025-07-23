#include <iostream>
#include <windows.h>
#include <conio.h>
#include "GameRegular.h"
#include "GameSave.h"
#include "GameLoad.h"

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string(argv[1]) == "-save") {
        GameSave game;
        game.main_menu();
    }
    else if (argc == 2 && std::string(argv[1]) == "-load") {
        GameLoad game(false);
        game.Run(1);
    }
    else if (argc == 3 && std::string(argv[1]) == "-load" && std::string(argv[2]) == "-silent") {
        GameLoad game(true);
        game.Run(1);
    }
    else {
        GameRegular game;
        game.main_menu();
    }

    return 0;
}