//
// Created by egor on 16.03.2020.
//

#ifndef OOP_LB1__2_SWORDMANFACTORY_H
#define OOP_LB1__2_SWORDMANFACTORY_H

#include "UnitFactory.h"
#include "../SwordMan/ShildMan.h"
#include "../SwordMan/LongSwordMan.h"

class SwordManFactory : UnitFactory {
public:
    ShildMan* createLotHealth() { return new ShildMan(); }
    LongSwordMan* createDamageDelear() { return new LongSwordMan(); }

};


#endif //OOP_LB1__2_SWORDMANFACTORY_H
