#include "unit.h"

Unit::Unit(int health, int damage, int armor, int speed)
{
    mainAttributes = new Attributes();
    setHealth(health);
    setDamage(damage);
    setArmor(armor);
    setSpeed(speed);
    //qDebug() << "Unit with arg ";
}

int Unit::getHealth() const
{
    return mainAttributes->health;
}

int Unit::getDamage() const
{
    return mainAttributes->damage;
}

int Unit::getArmor() const
{
    return mainAttributes->armor;
}

int Unit::getSpeed() const
{
    return mainAttributes->speed;
}

int Unit::getTypeOfAttack() const
{
    return mainAttributes->typeOfAttack;
}

void Unit::setHealth(const int value)
{
    mainAttributes->health = value;
}

void Unit::setDamage(const int value)
{
    mainAttributes->damage = value;
}

void Unit::setArmor(const int value)
{
    mainAttributes->armor = value;
}

void Unit::setSpeed(const int value)
{
    mainAttributes->speed = value;
}

void Unit::setTypeOfAttack(const int value)
{
    mainAttributes->typeOfAttack = value;
}

