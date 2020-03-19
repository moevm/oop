#include "bowweaponfactory.h"


std::shared_ptr<Weapon> BowWeaponFactory::createWeapon() const
{
    return std::make_shared<Bow>();
}
