

#ifndef CombatObjectTypeFactory_hpp
#define CombatObjectTypeFactory_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "CombatObjectType.hpp"

class CombatObjectTypeFactory
{
private:
    std::vector<CombatObjectType *> combatObjectTypes;
    unsigned int quantityOfTypes;

public:
    CombatObjectTypeFactory();
    CombatObjectType *getCombatObjectType(double health, double damage, double armor);
};

#endif /* CombatObjectTypeFactory_hpp */
