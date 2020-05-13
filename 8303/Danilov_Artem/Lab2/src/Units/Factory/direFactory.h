//
// Created by kot on 08.05.2020.
//

#ifndef DIREFACTORY_H
#define DIREFACTORY_H
#include "unitFactory.h"
#include "../Melee/ork.h"
#include "../Support/witch.h"
#include "../Range/chimera.h"


class DireFactory: public UnitFactory
{
public:
    Melee* createMelee() {return  new Ork();};
    Support* createSupport() {return  new Witch();}
    Range* createRange() {return new Chimera();}
};

#endif //DIREFACTORY_H
