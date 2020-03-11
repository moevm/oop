#include "noweapon.h"


NoWeapon::NoWeapon()
{
    radius = NO_RADIUS;
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


std::unique_ptr<Weapon> NoWeapon::clone()
{
    std::unique_ptr<Weapon> weapon(new NoWeapon(*this));
    return weapon;
}


size_t NoWeapon::getDamage() const
{
    return damage;
}


size_t NoWeapon::getRadiusAttack() const
{
    return radius;
}


size_t NoWeapon::getDistanceAttack() const
{
    return distance;
}
