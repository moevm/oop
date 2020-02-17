#include "magic.h"


Magic::Magic()
{
    radius = MAGIC_RADIUS;
    distance = RANGE_DISTANCE;
    damage = MAGIC_DMG;
}


Magic::Magic(const Magic& weapon)
{
    this->doCopy(weapon);
}


Magic& Magic::operator=(const Magic& weapon)
{
    if (this == &weapon) {
        return *this;
    }

    this->doCopy(weapon);

    return *this;
}


size_t Magic::getDamage() const
{
    return damage;
}


std::unique_ptr<Weapon> Magic::clone()
{
    std::unique_ptr<Weapon> weapon(new Magic(*this));
    return weapon;
}


size_t Magic::getRadiusAttack() const
{
    return radius;
}


size_t Magic::getDistanceAttack() const
{
    return distance;
}
