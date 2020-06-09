#ifndef FACADE_H
#define FACADE_H
//#include "Command.h"
#include "Field.h"
#include "ChainOfCommand.h"

class Facade
{
private:
    Field *field;
    chainOfResponsibility *basecomm;

public:
    void createField();
    void play();
};

#endif // FACADE_H
