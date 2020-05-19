#ifndef ADAPTER_H
#define ADAPTER_H
#include <sstream>
#include "units.h"

class Base;
class Adapter
{
public:
    Adapter();
    static std::string adaptUnitCreate(Unit*);
    static std::string adaptUnitMove(Unit*, int, int);
    static std::string adaptUnitUnderAttack(Unit*);
    static std::string adaptUnitPrint(Unit*);
    static std::string adaptUnitRemove(Unit*);
    static std::string adaptBaseCreate(Base*);
    static std::string adaptBaseUnderAttack(Base*);
    static std::string adaptGameOver(Base*);
};

#endif // ADAPTER_H
