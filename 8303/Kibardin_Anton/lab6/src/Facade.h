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
    BaseHandler* setBaseHandler;
    BaseHandler* setUnitHandler;
    BaseHandler* moveUnitRightHandler;
    BaseHandler* moveUnitLeftHandler;
    BaseHandler* moveUnitUpHandler;
    BaseHandler* moveUnitDownHandler;
    BaseHandler* attackUnitHandler;
    BaseHandler* showStatusHandler;
    BaseHandler* helpHandler;
    BaseHandler* adapterHandler;
    BaseHandler* turnOnOffLog;
    BaseHandler* saveHandler;
    BaseHandler* loadHandler;
public:

    void startGame();
    void play();
};


#endif //OOP_1_FACADE_H
