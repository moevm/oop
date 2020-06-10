#include "Unit.h"

Unit::Unit(string name) : Object(std::move(name))
{}

void Unit::add(const UnitPtr&)
{
    throw std::runtime_error("IUnit: method \"add\" call "
                             "without definition");
}

void Unit::remove(const UnitPtr&)
{
    throw std::runtime_error("IUnit: method \"remove\" call"
                             "without definition");
}

void Unit::attack()
{
    mediator->attack(this);
}
