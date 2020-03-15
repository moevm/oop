#include "units.h"
bool Unit::canMove()
{
    return this->movement;
}
void Unit::enableAttack(bool t)
{
    this->attacks = t;
}

void Unit::enableMovement(bool t)
{
    this->movement = t;
}

void Unit::buffHealth(float n)
{
    this->param.health = this->param.health * n;
}

void Unit::buffAttack(float n)
{
    this->param.damage = this->param.damage * n;
}

void Unit::buffArmor(float n)
{
    this->param.armor = this->param.armor * n;
}
QString Unit::getClassName()
{
    return this->className;
}

int Unit::getHealth()
{
    return this->param.health;
}
