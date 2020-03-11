#include "magicweaponfactory.h"


std::unique_ptr<Weapon> MagicWeaponFactory::createWeapon()
{
    std::unique_ptr<Weapon> weapon(new Magic);

    return weapon;
}
