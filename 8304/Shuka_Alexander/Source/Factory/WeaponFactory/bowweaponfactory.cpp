#include "bowweaponfactory.h"


std::unique_ptr<Weapon> BowWeaponFactory::createWeapon()
{
    std::unique_ptr<Weapon> weapon(new Bow);

    return weapon;
}
