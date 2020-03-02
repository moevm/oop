#ifndef FACTORYOFHORSEMAN_H
#define FACTORYOFHORSEMAN_H

#include "factoryofunits.h"
#include "horsemanwithspear.h"
#include "horsemanwithsword.h"

class FactoryOfHorsemen : public FactoryOfUnits
{
public:
    HorsemanWithSword* createFirstType(){ return new HorsemanWithSword(); }
    HorsemanWithSpear* createSecondType() {return new HorsemanWithSpear(); }
};

#endif // FACTORYOFHORSEMAN_H
