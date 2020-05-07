//
// Created by anton on 05.05.2020.
//

#ifndef OOP_1_GAME_H
#define OOP_1_GAME_H


#include "Facade.h"

class Game {
    Facade* facade;
    int gameMode;

    void createGame();
    int modeBases();
    int modeTitans();

public:
    int menu();
};


#endif //OOP_1_GAME_H
