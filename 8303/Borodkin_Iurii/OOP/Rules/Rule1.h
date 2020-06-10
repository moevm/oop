#ifndef RULE1_H
#define RULE1_H

#include "GameField.h"
#include "States.h"

class Rule1
{
public:
    Rule1();
    GameField* getField();
    State* getNextState(unsigned);
    bool endGame();
    ~Rule1();
private:
    State* currState = nullptr;
    GameField* gameField;
};

#endif // RULE1_H
