#ifndef FACADE_H
#define FACADE_H

#include "gamefield.h"
#include "basehandler.h"
#include "mediator.h"

class Facade
{
    GameField* field;
    BaseHandler* baseHandler;
    Mediator* mediator;

    CreateBaseHandler* createBaseHandler;
    CreateUnitHandler* createUnitHandler;
    MoveUnitHandler* moveUnitHandler;
    BaseStatusHandler* baseStatusHandler;
    AttackHandler* attackHandler;
    WrongCommandHandler* wrongCommandHandler;

public:
    Facade();
    void prepareGame();
    void startGame();
};

#endif // FACADE_H
