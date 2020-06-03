#ifndef UnitDPSFactory_hpp
#define UnitDPSFactory_hpp

#include <stdio.h>

#include "UnitAbstractFactory.hpp"
#include "varietyUnits/infantry/InfantryDPS.hpp"
#include "varietyUnits/cavalry/CavalryDPS.hpp"
#include "varietyUnits/archer/ArcherDPS.hpp"

class UnitDPSFactory : public UnitAbstractFactory
{
public:
    InfantryClass *createInfantry(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ override;
    CavalryClass *createCavalry(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ override;
    ArcherClass *createArcher(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ override;
};

#endif /* UnitDPSFactory_hpp */
