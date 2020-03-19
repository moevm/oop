#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "Field/gamefield.h"
#include "UnitBuilder/unitdirector.h"


enum class COMMAND : int
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STAY,
    EXIT,
    ADD_UNIT
};


class Game
{
public:
    Game(size_t width = 15, size_t height = 10);

    void run();

private:
    void draw();
    bool logic(COMMAND command);
    COMMAND input();

private:
    bool isRun;
    GameField gameField;
};

#endif // GAME_H
