#ifndef GAME_H
#define GAME_H

#include "GameField.h"
#include "Rules/Rule1.h"
#include "Rules/Rule2.h"
#include "Players/Players2.h"
#include "Players/Players3.h"

template <typename T, typename N>
class Game
{
    friend class MainWindow;

public:
    Game(GameField*&);
    State* getNextState();
    bool endGame();
private:
    T rule;
    N players;
    GameField* &gameField;
};

#endif // GAME_H
