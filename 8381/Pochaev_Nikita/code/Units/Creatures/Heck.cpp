#include "Heck.h"

Heck::Heck()
{
    health = 13;
    armor = 0;
    meleeAttackStrength = 5;
    actionTokens = 1;
    movementRange = HECK_MOVEMENT_RANGE;
}

Heck::Heck(std::string inputName) : Heck()
{
    name = std::move(inputName);
}

Heck* Heck::clone() const
{
    return new Heck(*this);
}

void Heck::describeYourself()
{
    std::cout << "Heck:" << std::endl;
    Unit::describeYourself();
}

std::string Heck::getUnitInf()
{
    return "Heck:\n" + Unit::getUnitInf();
}

void Heck::train()
{

}

bool Heck::cowardice()
{
    return false;
}

Heck::~Heck()
{

}

eUnitsType Heck::getType()
{
    return CANNON_FODDER;
}
