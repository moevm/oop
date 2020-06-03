#ifndef ArcherTank_hpp
#define ArcherTank_hpp

#include <stdio.h>
#include "../../../UnitTank.hpp"
#include "ArcherClass.hpp"

class ArcherTank : public UnitTank, public ArcherClass
{
private:
        

public:
    ArcherTank(std::string playerID, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory);
    
    
};

#endif /* ArcherTank_hpp */
