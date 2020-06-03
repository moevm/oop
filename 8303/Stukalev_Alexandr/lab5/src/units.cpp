#include "units.h"
#include "mediator.h"
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
string Unit::getClassName() const
{
    return this->className;
}

int Unit::getHealth() const
{
    return this->param.health;
}

int Unit::getDamage() const
{
    return this->param.damage;
}

int Unit::getArmor() const
{
    return this->param.armor;
}

bool Unit::getChoose()
{
    return this->choose;
}

void Unit::setChoose(bool t)
{
    this->choose = t;
}

void Unit::setArmy(char c)
{
    this->baseType = c;
}

void Unit::setHealth(int n)
{
    this->param.health = n;
}

void Unit::setDamage(int n)
{
    this->param.damage = n;
}

void Unit::setArmor(int n)
{
    this->param.armor = n;
}

char Unit::getArmy()
{
    return this->baseType;
}

int Unit::getX() const
{
    return this->x;
}

int Unit::getY() const
{
    return this->y;
}

void Unit::attackThis(int n)
{
    this->param.health -= n;
    LoggingProxy::logUnitAttacked(this);
    if(this->param.health  <= 0)
    {
        this->notify();
    }
}

char Unit::getName()
{
    return this->designation;
}
