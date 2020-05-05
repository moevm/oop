#ifndef FACADE_H
#define FACADE_H
#include "field.h"
#include "command.h"
#include "logging.h"
#include "chainofrespons.h"
#include "snapshot.h"
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
    ElemLoadComm* elemLoadComm;
    ElemSaveComm* elemSaveComm;
    Snapshot* snapshot;
public:
    Facade();
    void start();
};

#endif // FACADE_H
