#ifndef CavalryDPS_hpp
#define CavalryDPS_hpp

#include <stdio.h>
#include "../../../UnitDPS.hpp"
#include "CavalryClass.hpp"

class CavalryDPS : public UnitDPS, public CavalryClass
{
private:
        

public:
    CavalryDPS(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory);
    
    
};

#endif /* CavalryDPS_hpp */
