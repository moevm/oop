#ifndef UnitAbstractFactory_hpp
#define UnitAbstractFactory_hpp

#include <stdio.h>
#include <string>

#include "varietyUnits/infantry/InfantryClass.hpp"
#include "varietyUnits/cavalry/CavalryClass.hpp"
#include "varietyUnits/archer/ArcherClass.hpp"
#include "../../CombatObjectTypeFactory.hpp"

class Base;
class UnitAbstractFactory
{
public:
    virtual InfantryClass *createInfantry(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ = 0;
    virtual CavalryClass *createCavalry(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ = 0;
    virtual ArcherClass *createArcher(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ = 0;
};

#endif /* UnitAbstractFactory_hpp */
