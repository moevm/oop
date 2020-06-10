#ifndef RULE2_H
#define RULE2_H

#include "GameField.h"
#include "States.h"

class Rule2
{
public:
    Rule2();
    GameField* getField();
    State* getNextState(unsigned);
    bool endGame();
    ~Rule2();
private:
    State* currState = nullptr;
    GameField* gameField;
};

#endif // RULE2_H
