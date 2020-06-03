#ifndef UnitTankFactory_hpp
#define UnitTankFactory_hpp

#include <stdio.h>

#include "UnitAbstractFactory.hpp"
#include "varietyUnits/infantry/InfantryTank.hpp"
#include "varietyUnits/cavalry/CavalryTank.hpp"
#include "varietyUnits/archer/ArcherTank.hpp"

class UnitTankFactory : public UnitAbstractFactory
{
public:
    InfantryClass *createInfantry(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ override;
    CavalryClass *createCavalry(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ override;
    ArcherClass *createArcher(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ override;
};

#endif /* UnitTankFactory_hpp */
