#include "weapon.h"


void Weapon::doCopy(const Weapon& weapon)
{
    this->damage = weapon.damage;
    this->distance = weapon.distance;
}
