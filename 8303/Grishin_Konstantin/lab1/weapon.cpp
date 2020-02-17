#include "weapon.h"

Weapon::Weapon(Shell::Type type, int durability, float dmg_fact)
{
    this->type = type;
    iMaxDurability = durability;
    iDurability = durability;
    fDamageFactor = dmg_fact;
}


Club::Club(Shell::Type type, int durability, int damage, float dmg_fact):
    Weapon(type, durability, dmg_fact)
{
    this->type = type;
    fDamageFactor *= damage;
}


Shell Club::attack()
{
    return Shell{type, 0};
}
