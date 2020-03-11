#include "swordweaponfactory.h"


std::unique_ptr<Weapon> SwordWeaponFactory::createWeapon()
{
    std::unique_ptr<Weapon> weapon(new Sword);

    return weapon;
}
