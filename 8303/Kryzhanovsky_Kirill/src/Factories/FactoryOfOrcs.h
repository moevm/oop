//
// Created by therealyou on 05.03.2020.
//

#ifndef LAB1_FACTORYOFORCS_H
#define LAB1_FACTORYOFORCS_H


#include "FactoryOfUnits.h"
#include "../Units/Goblin.h"
#include "../Units/Troll.h"

class FactoryOfOrcs : public FactoryOfUnits{
public:
    Goblin* createGoblin();
    Troll* createTroll();
};


#endif //LAB1_FACTORYOFORCS_H
