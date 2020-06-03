#ifndef InfantryDPS_hpp
#define InfantryDPS_hpp

#include <stdio.h>
#include "../../../UnitDPS.hpp"
#include "InfantryClass.hpp"

class InfantryDPS : public UnitDPS, public InfantryClass
{
private:
    

public:
    InfantryDPS(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory);
    
    
};

#endif /* InfantryDPS_hpp */
