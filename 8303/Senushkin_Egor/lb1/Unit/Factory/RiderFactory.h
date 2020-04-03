//
// Created by egor on 16.03.2020.
//

#ifndef OOP_LB1__2_RIDERFACTORY_H
#define OOP_LB1__2_RIDERFACTORY_H

#include "UnitFactory.h"
#include "../Rider/SpearHorse.h"
#include "../Rider/HeavyCavalry.h"

class RiderFactory : UnitFactory{
public:
    SpearHorse* createDamageDelear() { return new SpearHorse(); }
    HeavyCavalry* createLotHealth() { return new HeavyCavalry(); }
};

#endif //OOP_LB1__2_RIDERFACTORY_H
