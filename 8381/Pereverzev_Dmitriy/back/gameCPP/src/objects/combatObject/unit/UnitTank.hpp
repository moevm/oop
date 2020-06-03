#ifndef UnitTank_hpp
#define UnitTank_hpp

#include <stdio.h>

#include "Unit.hpp"

class UnitTank : public virtual Unit /*, CombatObject */
{
protected:
    double critChance;
    double critAbsorption;

public:
    void underAttack(double damage, double armor);
    v8::Local<v8::Object> getFullInfo();
};

#endif /* UnitTank_hpp */
