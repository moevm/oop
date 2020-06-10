#include "Game.h"

template<>
Game<Rule1, Players2>::Game(GameField* &gf) : gameField(gf)
{
    gameField = rule.getField();
    gameField->addBase(new Base("", unsigned(gameField->maxNumUnitsBase), 1), {8, 0});
    gameField->addBase(new Base("", unsigned(gameField->maxNumUnitsBase), 2), {0, 8});
}

template<>
Game<Rule1, Players3>::Game(GameField* &gf) : gameField(gf)
{
    gameField = rule.getField();
    gameField->addBase(new Base("", unsigned(gameField->maxNumUnitsBase), 1), {8, 0});
    gameField->addBase(new Base("", unsigned(gameField->maxNumUnitsBase), 2), {0, 8});

    for (size_t i = 4; i < 6; i++)
        for (size_t j = 4; j < 6; j++)
        {
            delete gameField->at({i,j}).landscape;
            gameField->at({i,j}).landscape = new Landscape;
            gameField->at({i,j}).brush = gameField->at({i,j}).landscape->brush();
        }

    gameField->addBase(new Base("", unsigned(gameField->maxNumUnitsBase), 3), {4, 4});
}

template<>
Game<Rule2, Players2>::Game(GameField* &gf) : gameField(gf)
{
    gameField = rule.getField();
    gameField->addBase(new Base("", unsigned(gameField->maxNumUnitsBase), 1), {0, 0});
    gameField->addBase(new Base("", unsigned(gameField->maxNumUnitsBase), 2), {13, 13});
}

template<>
Game<Rule2, Players3>::Game(GameField* &gf) : gameField(gf)
{
    gameField = rule.getField();
    gameField->addBase(new Base("", unsigned(gameField->maxNumUnitsBase), 1), {0, 0});
    gameField->addBase(new Base("", unsigned(gameField->maxNumUnitsBase), 2), {13, 13});
    gameField->addBase(new Base("", unsigned(gameField->maxNumUnitsBase), 3), {0, 13});
}

template <>
State* Game<Rule1, Players2>::getNextState()
{
    auto state = rule.getNextState(2);
    state->setGameField(gameField);
    return state;
}

template <>
State* Game<Rule1, Players3>::getNextState()
{
    auto state = rule.getNextState(3);
    state->setGameField(gameField);
    return state;
}

template <>
State* Game<Rule2, Players2>::getNextState()
{
    auto state = rule.getNextState(2);
    state->setGameField(gameField);
    return state;
}

template <>
State* Game<Rule2, Players3>::getNextState()
{
    auto state = rule.getNextState(3);
    state->setGameField(gameField);
    return state;
}

template <>
bool Game<Rule2, Players2>::endGame()
{
    return rule.endGame();
}

template <>
bool Game<Rule2, Players3>::endGame()
{
    return rule.endGame();
}

template <>
bool Game<Rule1, Players2>::endGame()
{
    return rule.endGame();
}

template <>
bool Game<Rule1, Players3>::endGame()
{
    return rule.endGame();
}
