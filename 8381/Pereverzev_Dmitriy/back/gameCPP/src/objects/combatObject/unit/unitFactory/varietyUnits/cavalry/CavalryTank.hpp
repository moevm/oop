#ifndef CavalryTank_hpp
#define CavalryTank_hpp

#include <stdio.h>
#include "../../../UnitTank.hpp"
#include "CavalryClass.hpp"

class CavalryTank : public UnitTank, public CavalryClass
{
private:
        

public:
    CavalryTank(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory);
    
    
};

#endif /* CavalryTank_hpp */
