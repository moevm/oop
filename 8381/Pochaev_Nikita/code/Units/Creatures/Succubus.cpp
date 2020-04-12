#include "Succubus.h"

Succubus::Succubus()
{
    health = 15;
    armor = 0;
    meleeAttackStrength = 3;
    actionTokens = 2;
    movementRange = SUCCUBUS_MOVEMENT_RANGE;
}

Succubus::Succubus(std::string inputName) : Succubus()
{
    name = std::move(inputName);
}

Succubus* Succubus::clone() const
{
    return new Succubus(*this);
}

void Succubus::describeYourself()
{
    std::cout << "Succubus:" << std::endl;
    Unit::describeYourself();
}

std::string Succubus::getUnitInf()
{
    return "Succubus:\n" + Unit::getUnitInf();
}

void Succubus::shot()
{

}

void Succubus::canopyShooting()
{

}

Succubus::~Succubus()
{

}

eUnitsType Succubus::getType()
{
    return SHOOTER;
}
