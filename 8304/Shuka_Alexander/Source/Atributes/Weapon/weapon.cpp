#include "weapon.h"


void Weapon::doCopy(const Weapon& weapon)
{
    this->damage = weapon.damage;
    this->radius = weapon.radius;
    this->distance = weapon.distance;
}
