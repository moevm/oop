#include "Rule1.h"

Rule1::Rule1() : gameField(new GameField(10, 10, 10, 5))
{
    for (size_t i = 5; i < 10; i++)
        (*gameField)[2][i].landscape = new Rock;

    for (size_t i = 0; i < 5; i++)
        (*gameField)[7][i].landscape = new Rock;

    (*gameField)[4][4].landscape = new Lava;
    (*gameField)[4][5].landscape = new Lava;
    (*gameField)[5][4].landscape = new Lava;
    (*gameField)[5][5].landscape = new Lava;

    (*gameField)[4][9].landscape = new Water;
    (*gameField)[5][9].landscape = new Water;
    (*gameField)[4][0].landscape = new Water;
    (*gameField)[5][0].landscape = new Water;

    for (size_t i = 0; i < gameField->height(); i++)
        for (size_t j = 0; j < gameField->width(); j++)
        {
            if (!(*gameField)[i][j].landscape)
                (*gameField)[i][j].landscape = new Landscape;

            (*gameField)[i][j].brush = (*gameField)[i][j].landscape->brush();
        }

}

bool Rule1::endGame()
{
    return gameField->bases() == 1;
}

State* Rule1::getNextState(unsigned players)
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

GameField* Rule1::getField()
{
    return gameField;
}

Rule1::~Rule1()
{
    delete gameField;
    delete currState;
}
