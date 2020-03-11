#include "noweaponfactory.h"


std::unique_ptr<Weapon> NoWeaponFactory::createWeapon()
{
    std::unique_ptr<Weapon> weapon(new NoWeapon);

    return weapon;
}

