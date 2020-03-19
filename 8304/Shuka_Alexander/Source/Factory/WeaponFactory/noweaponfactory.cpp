#include "noweaponfactory.h"


std::shared_ptr<Weapon> NoWeaponFactory::createWeapon() const
{
    return std::make_shared<NoWeapon>();
}

