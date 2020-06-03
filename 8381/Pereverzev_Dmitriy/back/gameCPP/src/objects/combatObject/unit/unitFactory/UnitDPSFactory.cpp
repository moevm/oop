#include "UnitDPSFactory.hpp"

InfantryClass *UnitDPSFactory::createInfantry(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ { return new InfantryDPS(playerID, unitID, combatObjectTypeFactory); }
CavalryClass *UnitDPSFactory::createCavalry(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ { return new CavalryDPS(playerID, unitID, combatObjectTypeFactory); }
ArcherClass *UnitDPSFactory::createArcher(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory) /*const*/ { return new ArcherDPS(playerID, unitID, combatObjectTypeFactory); }
