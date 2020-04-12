#include "Peasant.h"

Peasant::Peasant()
{
    health = 10;
    armor = 5;
    meleeAttackStrength = 5;
    actionTokens = 1;
    movementRange = PEASANT_MOVEMENT_RANGE;
}

Peasant::Peasant(std::string inputName) : Peasant()
{
    name = std::move(inputName);
}

Peasant* Peasant::clone() const
{
    return new Peasant(*this);
}

void Peasant::describeYourself()
{
    std::cout << "Peasant:" << std::endl;
    Unit::describeYourself();
}

std::string Peasant::getUnitInf()
{
    return "Peasant:\n" + Unit::getUnitInf();
}

void Peasant::train()
{

}

bool Peasant::cowardice()
{
    return false;
}

Peasant::~Peasant()
{

}

eUnitsType Peasant::getType()
{
    return CANNON_FODDER;
}
