#include "sword.h"


Sword::Sword()
{
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


std::shared_ptr<Weapon> Sword::clone() const
{
    return std::make_shared<Sword>(*this);
}


size_t Sword::getDistanceAttack() const
{
    return  distance;
}
