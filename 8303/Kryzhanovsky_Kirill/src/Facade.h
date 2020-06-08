//
// Created by therealyou on 06.04.2020.
//

#ifndef LAB1_FACADE_H
#define LAB1_FACADE_H

#include "GameField.h"
#include "BaseHandler.h"

class Facade {
    GameField *gameField;
    Adapter *adapter;

    BaseHandler *baseHandler;
    BaseHandler *setBaseHandler;
    BaseHandler *setUnitHandler;
    BaseHandler *moveUnitRightHandler;
    BaseHandler *moveUnitLeftHandler;
    BaseHandler *moveUnitUpHandler;
    BaseHandler *moveUnitDownHandler;
    BaseHandler *attackUnitHandler;
    BaseHandler *showStatusHandler;
    BaseHandler *helpHandler;
    BaseHandler *adapterHandler;
    BaseHandler *turnOnOffLog;
    BaseHandler* saveHandler;
    BaseHandler* loadHandler;

public:
    Facade();

    void startGame();

    void play();
};


#endif //LAB1_FACADE_H
