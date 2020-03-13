#include "swordweaponfactory.h"


std::shared_ptr<Weapon> SwordWeaponFactory::createWeapon() const
{
    return std::make_shared<Sword>();
}
