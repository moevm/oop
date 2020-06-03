#include "CavalryTank.hpp"

CavalryTank::CavalryTank(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory)
{
    health = 175;
    
    type = combatObjectTypeFactory->getCombatObjectType(80, 40, 1);
    this->playerID = playerID;
    this->ID = unitID;

    critChance = 0.15;
    critAbsorption = 0.5;
    objectType = CAV_TANK;
}












