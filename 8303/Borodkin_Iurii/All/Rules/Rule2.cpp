#include "Rule2.h"

Rule2::Rule2() : gameField(new GameField(15, 15, 20, 5))
{
    for (size_t i = 10; i < 14; i++)
        for (size_t j = 1; j < 5; j++)
            (*gameField)[i][j].landscape = new Lava;

    (*gameField)[9][6].landscape = new Lava;
    (*gameField)[9][5].landscape = new Lava;
    (*gameField)[10][5].landscape = new Lava;
    (*gameField)[11][5].landscape = new Lava;
    (*gameField)[13][5].landscape = new Lava;


    for (size_t j = 0; j < 6; j++)
    {
        (*gameField)[7][j].landscape = new Rock;
        (*gameField)[j][7].landscape = new Rock;
    }

    for (size_t j = 9; j < 15; j++)
    {
        (*gameField)[7][j].landscape = new Rock;
        (*gameField)[j][7].landscape = new Rock;
    }

    (*gameField)[7][7].landscape = new Water;

    for (size_t i = 0; i < gameField->height(); i++)
        for (size_t j = 0; j < gameField->width(); j++)
        {
            if (!(*gameField)[i][j].landscape)
                (*gameField)[i][j].landscape = new Landscape;

            (*gameField)[i][j].brush = (*gameField)[i][j].landscape->brush();
        }

}

bool Rule2::endGame()
{
    return gameField->bases() == 1;
}


GameField* Rule2::getField()
{
    return gameField;
}

State* Rule2::getNextState(unsigned players)
{
    static unsigned long long curr = 0;
    delete currState;

    if (players == 2) {

        if (curr % 2) {

            currState = new State1;

        } else {

            currState = new State2;

        }

    } else if (players == 3) {

        if (curr % 3 == 0) {

            currState = new State1;

        } else if (curr % 3 == 1) {

            currState = new State2;

        } else {

            currState = new State3;

        }
    }

    curr++;

    return currState;
}

Rule2::~Rule2()
{
    delete gameField;
    delete currState;
}
