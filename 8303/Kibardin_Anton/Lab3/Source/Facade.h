//
// Created by anton on 03.04.2020.
//

#ifndef OOP_1_FACADE_H
#define OOP_1_FACADE_H

#include <iostream>
#include "Field.h"
#include "Handler.h"

class Facade {
    Field* field;

    BaseHandler* baseHandler;
    SetBaseHandler* setBaseHandler;
    SetUnitHandler* setUnitHandler;
    MoveUnitRightHandler* moveUnitRightHandler;
    MoveUnitLeftHandler* moveUnitLeftHandler;
    MoveUnitUpHandler* moveUnitUpHandler;
    MoveUnitDownHandler* moveUnitDownHandler;
    AttackUnitHandler* attackUnitHandler;
    ShowStatusHandler* showStatusHandler;
    HelpHandler* helpHandler;
public:

    void startGame();
    void play();
};


#endif //OOP_1_FACADE_H
