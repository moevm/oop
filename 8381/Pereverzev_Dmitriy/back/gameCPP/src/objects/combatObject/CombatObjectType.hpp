

#ifndef CombatObjectType_hpp
#define CombatObjectType_hpp

#include <stdio.h>
#include <vector>

class CombatObjectType
{
private:
    double maxHealth;
    double damage;
    double armor;

public:
    CombatObjectType(double health, double damage, double armor);

    double getMaxHealth() const;
    double getDamage() const;
    double getArmor() const;


    bool dataСomparison(double health, double damage, double armor);
};

#endif /* CombatObjectType_hpp */
