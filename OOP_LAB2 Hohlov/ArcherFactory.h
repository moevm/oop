
#ifndef OOP_LAB1_ARCHERFACTORY_H
#define OOP_LAB1_ARCHERFACTORY_H


#include "UnitFactory.h"
#include "Sniper.h"
#include "CrossBowMan.h"

class ArcherFactory: UnitFactory {

public:
    CrossBowMan *createFirst(){ return new CrossBowMan; }
    Sniper *createSecond(){ return new Sniper(); }

};

#endif //OOP_LAB1_ARCHERFACTORY_H
