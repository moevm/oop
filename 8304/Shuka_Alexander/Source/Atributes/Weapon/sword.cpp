#include "sword.h"


Sword::Sword()
{
    radius = SWORD_RADIUS;
    distance = MELEE_DISTANCE;
    damage = SWORD_DMG;
}


Sword::Sword(const Sword& weapon)
{
    this->doCopy(weapon);
}


Sword& Sword::operator=(const Sword& weapon)
{
    if (this == &weapon) {
        return *this;
    }

    this->doCopy(weapon);

    return *this;
}


size_t Sword::getDamage() const
{
    return damage;
}


std::unique_ptr<Weapon> Sword::clone()
{
    std::unique_ptr<Weapon> weapon(new Sword(*this));
    return weapon;
}


size_t Sword::getRadiusAttack() const
{
    return radius;
}


size_t Sword::getDistanceAttack() const
{
    return  distance;
}
