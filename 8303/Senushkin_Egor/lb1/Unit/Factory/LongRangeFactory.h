//
// Created by egor on 16.03.2020.
//

#ifndef OOP_LB1__2_LONGRANGEFACTORY_H
#define OOP_LB1__2_LONGRANGEFACTORY_H

#include "UnitFactory.h"
#include "../LongRange/Archer.h"
#include "../LongRange/Wizard.h"

class LongRangeFactory : UnitFactory {
public:
    Wizard* createDamageDelear() { return new Wizard();}
    Archer* createLotHealth() { return new Archer(); }
};

#endif //OOP_LB1__2_LONGRANGEFACTORY_H
