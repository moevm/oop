#include "Archer.h"

Archer::Archer()
{
    health = 15;
    armor = 5;
    meleeAttackStrength = 1;
    actionTokens = 2;
    movementRange = ARCHER_MOVEMENT_RANGE;
}

Archer::Archer(std::string inputName) : Archer()
{
    name = std::move(inputName);
}

Archer* Archer::clone() const
{
    return new Archer(*this);
}

void Archer::describeYourself()
{
    std::cout << "Archer:" << std::endl;
    Unit::describeYourself();
}

std::string Archer::getUnitInf()
{
    return "Archer:\n" + Unit::getUnitInf();
}

void Archer::shot()
{
    std::cout << "Shooting skill unique to shooters activated. From archer." << std::endl;
}

void Archer::canopyShooting()
{

}

Archer::~Archer()
{

}

eUnitsType Archer::getType()
{
     return SHOOTER;
}
