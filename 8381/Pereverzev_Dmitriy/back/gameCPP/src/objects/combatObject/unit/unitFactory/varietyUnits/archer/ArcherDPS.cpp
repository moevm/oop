
#include "ArcherDPS.hpp"

ArcherDPS::ArcherDPS(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory)
{
    health = 80;
    
    type = combatObjectTypeFactory->getCombatObjectType(80, 40, 1);
    this->playerID = playerID;
    this->ID = unitID;

    critChance = 0.2;
    critDamage = 2;
    objectType = ARCH_DPS;
}








