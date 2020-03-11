#include "bow.h"


Bow::Bow()
{
    radius = NO_RADIUS;
    distance = MELEE_DISTANCE;
    damage = SWORD_DMG;
}


Bow::Bow(const Bow& weapon)
{
    this->doCopy(weapon);
}


Bow& Bow::operator=(const Bow& weapon)
{
    if (this == &weapon) {
        return *this;
    }

    this->doCopy(weapon);

    return *this;
}


size_t Bow::getDamage() const
{
    return damage;
}


size_t Bow::getRadiusAttack() const
{
    return  radius;
}


size_t Bow::getDistanceAttack() const
{
    return  distance;
}


std::unique_ptr<Weapon> Bow::clone()
{
    std::unique_ptr<Weapon> weapon(new Bow(*this));
    return weapon;
}
