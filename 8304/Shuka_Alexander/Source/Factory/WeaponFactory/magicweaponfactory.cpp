#include "magicweaponfactory.h"


std::shared_ptr<Weapon> MagicWeaponFactory::createWeapon() const
{
    return std::make_shared<Magic>();
}
