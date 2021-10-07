#ifndef FACTORYOFINFANTRY_H
#define FACTORYOFINFANTRY_H

#include "factoryofunits.h"
#include "spearman.h"
#include "swordsman.h"

class FactoryOfInfantry : public FactoryOfUnits
{
public:
    Swordsman* createFirstType() {return new Swordsman();}
    Spearman* createSecondType() {return new Spearman();}
};

#endif // FACTORYOFINFANTRY_H
