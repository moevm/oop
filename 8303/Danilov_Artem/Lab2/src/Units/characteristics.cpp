//
// Created by kot on 28.02.2020.
//

#include "characteristics.h"



Characteristics::Characteristics()
{
    setAll(0,0,0);
}

void Characteristics::setAll(int health, int damage, int armor, int stepLimits)
{
    setHealth(health);
    setDamage(damage);
    setArmor(armor);
    setStepLimits(stepLimits);
}

int Characteristics::getHealth() const
{
    return health;
}

void Characteristics::setHealth(int value)
{
    health = value;
}

int Characteristics::getDamage() const
{
    return damage;
}

void Characteristics::setDamage(int value)
{
    damage = value;
}

int Characteristics::getArmor() const
{
    return armor;
}

void Characteristics::setArmor(int value)
{
    armor = value;
}

int Characteristics::getStepLimits() const
{
    return stepLimits;
}

void Characteristics::setStepLimits(int value)
{
    stepLimits = value;
}
