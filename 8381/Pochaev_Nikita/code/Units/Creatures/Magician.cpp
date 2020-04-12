#include "Magician.h"

Magician::Magician()
{
    health = 10;
    armor = 5;
    meleeAttackStrength = 5;
    actionTokens = 1;
    movementRange = MAGICIAN_MOVEMENT_RANGE;
}

Magician::Magician(std::string inputName) : Magician()
{
    name = std::move(inputName);
}

Magician* Magician::clone() const
{
    return new Magician(*this);
}

void Magician::describeYourself()
{
    std::cout << "Magician:" << std::endl;
    Unit::describeYourself();
}

std::string Magician::getUnitInf()
{
    return "Magician:\n" + Unit::getUnitInf();
}

void Magician::magicFist()
{

}

void Magician::healing()
{

}

Magician::~Magician()
{

}

eUnitsType Magician::getType()
{
    return WIZARD;
}
