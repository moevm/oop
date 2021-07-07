//
// Created by anton on 16.02.2020.
//

#include "Unit.h"

Unit::Unit():Unit({200, 200, 20, 2}){}

Unit::Unit(Specifications values):values(values), unitName("unnamed"), x(0), y(0) {}

void Unit::death() {
    this->notify();
}

void Unit::setName(std::string& name) {
    unitName = name;
}

void Unit::setX(int x)  {
    this->x = x;
}

void Unit::setY(int y)
{
    this->y = y;
}

int Unit::getX() const
{
    return x;
}

int Unit::getY() const {
    return y;
}

std::string Unit::getName() const
{
    return unitName;
}

void Unit::getDamage(int attackPower) {
    values.health -= attackPower;
    if(values.health <= 0)
        death();
}

void Unit::printSpecifications() const {
    printf("------------------\n");
    printf("class = %c\n", getClass());
    printf("health = %d\n", values.health);
    printf("attack range = %d\n", values.attackRange);
    printf("attack = %d\n", values.attack);
    printf("armor = %d\n", values.armor);
    printf("------------------\n");
}

std::ostream& operator<<(std::ostream& out, const Unit& unit)
{
    out << "name:" << unit.getName() << ", health: " << unit.values.health;
    out << ", armor: " << unit.values.armor << ", attack: " << unit.values.attack;
    out << ", attackRange: " << unit.values.attackRange;
    out << ", coordinate: " << unit.getX() << ", " << unit.getY() << std::endl;
}