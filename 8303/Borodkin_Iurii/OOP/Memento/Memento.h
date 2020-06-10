#ifndef MEMENTO_H
#define MEMENTO_H
#include "../GameField.h"
#include "Game.h"

class Memento
{
public:

    friend class GameSaveLoad;

    Memento(GameField*);
    GameField* getState() const;
    GameField* &getState();
    Game <Rule1, Players2>* game1 = nullptr;
    Game <Rule2, Players2>* game2 = nullptr;
    Game <Rule1, Players3>* game3 = nullptr;
    Game <Rule2, Players3>* game4 = nullptr;
private:
    GameField* state;
};

#endif // MEMENTO_H
