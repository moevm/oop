#ifndef FACTORYOFUNITS_H
#define FACTORYOFUNITS_H

#include "unit.h"

class FactoryOfUnits
{
public:
    virtual Unit* createFirstType() = 0;
    virtual Unit* createSecondType() = 0;
};

#endif // FACTORYOFUNITS_H
