#include "ArcherTank.hpp"

ArcherTank::ArcherTank(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory)
{
    health = 120;
    
    type = combatObjectTypeFactory->getCombatObjectType(120, 20, 1);
    this->playerID = playerID;
    this->ID = unitID;

    critChance = 0.1;
    critAbsorption = 0.3;
    objectType = ARCH_TANK;
}












