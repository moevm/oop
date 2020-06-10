#include "States.h"

void State::setGameField(GameField* gf)
{
    gameField = gf;
}

bool State::stateObject(std::pair<size_t, size_t> coords)
{
    return gameField->at(coords).obj->player == player();
}

unsigned State1::player()
{
    return 1;
}

unsigned State2::player()
{
    return 2;
}

unsigned State3::player()
{
    return 3;
}
