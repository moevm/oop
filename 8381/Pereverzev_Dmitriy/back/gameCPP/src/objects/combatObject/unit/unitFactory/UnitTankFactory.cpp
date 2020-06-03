#include "UnitTankFactory.hpp"

InfantryClass *UnitTankFactory::createInfantry(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ { return new InfantryTank(playerID, unitID, combatObjectTypeFactory); }
CavalryClass *UnitTankFactory::createCavalry(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ { return new CavalryTank(playerID, unitID, combatObjectTypeFactory); }
ArcherClass *UnitTankFactory::createArcher(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ { return new ArcherTank(playerID, unitID, combatObjectTypeFactory); }
