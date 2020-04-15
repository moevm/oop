#include "LegendaryWeapon.h"

void LegendaryWeapon::operator+=(const std::shared_ptr<Unit> &unit)
{
    unit->setMeleeAttackBoost(LEGENDARY_WEAPON_BOOST);
}

std::string LegendaryWeapon::getNameOfNeutralObject()
{
    return "Legendary weapon";
}
