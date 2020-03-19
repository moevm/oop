#include "noweapon.h"


NoWeapon::NoWeapon()
{
    distance = NO_DISTANCE;
    damage = NO_DMG;
}


NoWeapon::NoWeapon(const NoWeapon& weapon)
{
    this->doCopy(weapon);
}


NoWeapon& NoWeapon::operator=(const NoWeapon& weapon)
{
    if (this == &weapon) {
        return *this;
    }

    this->doCopy(weapon);

    return *this;
}


std::shared_ptr<Weapon> NoWeapon::clone() const
{
    return std::make_shared<NoWeapon>(*this);
}


size_t NoWeapon::getDamage() const
{
    return damage;
}


size_t NoWeapon::getDistanceAttack() const
{
    return distance;
}
