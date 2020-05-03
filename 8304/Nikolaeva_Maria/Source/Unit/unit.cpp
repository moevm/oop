#include "unit.h"


void Unit::toHurt(size_t dHealth)
{
    if (health - dHealth > __LONG_MAX__) {
        health = 0;
    } else
        this->health -= dHealth;
}

Armor* Unit::getArmor() const
{
    return this->armor;
}


bool Unit::setArmor(Armor* armor)
{
    if (this->armor != nullptr) {
        delete this->armor;
    }
    this->armor = armor;

    return true;
}


Weapon* Unit::getWeapon() const
{
    return this->weapon;
}


bool Unit::setWeapon(Weapon* weapon)
{
    if (this->weapon != nullptr) {
        delete this->weapon;
    }
    this->weapon = weapon;

    return true;
}


Point2D Unit::getCoordiante() const
{
    return *this->coordinate;
}


bool Unit::setCoordinate(Point2D* point)
{
    if (this->coordinate != nullptr) {
        delete coordinate;
    }
    this->coordinate = point;

    return true;
}


size_t Unit::getHealth()
{
    return this->health;
}


PLAYER Unit::getPlayer() const
{
    return this->player;
}


void Unit::setPlayer(PLAYER player)
{
    this->player = player;
}
