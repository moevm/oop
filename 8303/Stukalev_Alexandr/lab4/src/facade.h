#ifndef FACADE_H
#define FACADE_H
#include "field.h"
#include "command.h"
#include "logging.h"
#include "chainofrespons.h"
class Facade
{
    Field* field;
    ChainOfRespons* chainOfRespons;
    ElemUnitMove* elemUnitMove;
    ElemUnitCreat* elemUnitCreate;
    ElemUnitAttack* elemUnitAttack;
    ElemBaseStatus* elemBaseStatus;
    ElemLogging* elemLogging;
    ElemWrongComm* elemWrongComm;
public:
    Facade();
    void start();
};

#endif // FACADE_H
