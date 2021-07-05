//
// Created by kot on 28.02.2020.
//

#include "characteristics.h"



Characteristics::Characteristics()
{
    setAll(0,0,0);
}

void Characteristics::setAll(int strength, int agility, int intelligence,
        int health, int damage, int armor, int stepLimits) {

    setStrength(strength);
    setAgility(agility);
    setIntelligence(intelligence);
    setHealth(health);
    setDamage(damage);
    setArmor(armor);
    setStepLimits(stepLimits);

}

void Characteristics::setAll(int strength, int agility, int intelligence){
    setStrength(strength);
    setAgility(agility);
    setIntelligence(intelligence);
    setHealth(strength * 100);
    setDamage((strength+agility)*5);
    setArmor(agility*7);
    setStepLimits(agility/5);

}

int Characteristics::getStrength() const
{
    return strength;
}

void Characteristics::setStrength(int value)
{
    strength = value;
}

int Characteristics::getAgility() const
{
    return  agility;
}

void Characteristics::setAgility(int value)
{
    agility = value;
}

int Characteristics::getIntelligence() const
{
    return  intelligence;
}

void Characteristics::setIntelligence(int value)
{
    intelligence = value;
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
