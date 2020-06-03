#ifndef InfantryTank_hpp
#define InfantryTank_hpp

#include <stdio.h>
#include "../../../UnitTank.hpp"
#include "InfantryClass.hpp"

class InfantryTank : public UnitTank, public InfantryClass
{
private:
    

public:
    InfantryTank(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory);
    
    
};

#endif /* InfantryTank_hpp */
