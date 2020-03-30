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
QString Unit::getClassName()
{
    return this->className;
}

int Unit::getHealth()
{
    return this->param.health;
}

int Unit::getDamage()
{
    return this->param.damage;
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

char Unit::getArmy()
{
    return this->baseType;
}

int Unit::getX()
{
    return this->x;
}

int Unit::getY()
{
    return this->y;
}

void Unit::attackThis(int n)
{
    this->param.health -= n;
    if(this->param.health  <= 0)
    {
        this->notify();
    }
}
