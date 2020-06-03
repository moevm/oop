#ifndef ArcherDPS_hpp
#define ArcherDPS_hpp

#include <stdio.h>
#include "../../../UnitDPS.hpp"
#include "ArcherClass.hpp"

class ArcherDPS : public UnitDPS, public ArcherClass
{
private:
public:
    ArcherDPS(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory);

};

#endif /* ArcherDPS_hpp */
