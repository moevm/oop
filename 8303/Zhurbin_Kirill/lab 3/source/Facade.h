#ifndef OOP1_FACADE_H
#define OOP1_FACADE_H

#include "Field.h"
#include "Mediator.h"
#include "Handler.h"

class Facade{

private:
    Field* field;
    Mediator* mediator;
    BaseHandler* baseHandler;
    BaseHandler* setBase;
    BaseHandler* noCommand;
    BaseHandler* setUnit;
    BaseHandler* moveUnit;
    BaseHandler* statusBase;
    BaseHandler* attackUnit;

public:
    void createGame();
    void play();

};

#endif //OOP1_FACADE_H
