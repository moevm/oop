#include "Demon.h"

Demon::Demon()
{
    health = 15;
    armor = 5;
    meleeAttackStrength = 1;
    actionTokens = 2;
    movementRange = DEMON_MOVEMENT_RANGE;
}

Demon::Demon(std::string inputName) : Demon()
{
    name = std::move(inputName);
}

Demon* Demon::clone() const
{
    return new Demon(*this);
}

void Demon::describeYourself()
{
    std::cout << "Demon:" << std::endl;
    Unit::describeYourself();
}

std::string Demon::getUnitInf()
{
    return "Demon:\n" + Unit::getUnitInf();
}

void Demon::magicFist()
{

}

void Demon::healing()
{

}

Demon::~Demon()
{

}

eUnitsType Demon::getType()
{
    return WIZARD;
}
