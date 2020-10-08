//
// Created by kot on 08.05.2020.
//

#ifndef UNITFACTORY_H
#define UNITFACTORY_H


#include "../Melee/melee.h"
#include "../Support/support.h"
#include "../Range/range.h"

class UnitFactory {
public:
    virtual Melee* createMelee() = 0;
    virtual Support* createSupport() = 0;
    virtual Range* createRange() = 0;
};


#endif //UNITFACTORY_H
