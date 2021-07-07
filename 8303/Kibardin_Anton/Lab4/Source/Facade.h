//
// Created by anton on 03.04.2020.
//

#ifndef OOP_1_FACADE_H
#define OOP_1_FACADE_H

#include <iostream>
#include "Field.h"
#include "Handler.h"
#include "Adapter.h"



class Facade {
    Field* field;
    Adapter* adapter;


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
    SwitchLogHandler* adapterHandler;
    TurnOnOffLog* turnOnOffLog;
public:

    void startGame();
    void play();
};


#endif //OOP_1_FACADE_H
