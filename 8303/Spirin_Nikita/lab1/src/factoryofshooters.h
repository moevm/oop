#ifndef FACTORYOFSHOOTERS_H
#define FACTORYOFSHOOTERS_H

#include "factoryofunits.h"
#include "archer.h"
#include "crossbowman.h"

class FactoryOfShooters : public FactoryOfUnits
{
public:
    Archer* createFirstType(){ return new Archer(); }
    Crossbowman* createSecondType(){ return new Crossbowman(); }
};

#endif // FACTORYOFSHOOTERS_H
