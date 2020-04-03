//
// Created by egor on 16.03.2020.
//

#ifndef OOP_LB1__2_UNITFACTORY_H
#define OOP_LB1__2_UNITFACTORY_H

#include "../Unit.h"

class UnitFactory{
protected:
    virtual  Unit* createDamageDelear() = 0;
    virtual  Unit* createLotHealth()  = 0;
};

#endif //OOP_LB1__2_UNITFACTORY_H
