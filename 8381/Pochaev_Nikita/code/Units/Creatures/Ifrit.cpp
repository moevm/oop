#include "Ifrit.h"

Ifrit::Ifrit()
{
    health = 10;
    armor = 15;
    meleeAttackStrength = 7;
    actionTokens = 2;
    movementRange = IFRIT_MOVEMENT_RANGE;
}

Ifrit::Ifrit(std::string inputName) : Ifrit()
{
    name = std::move(inputName);
}

Ifrit* Ifrit::clone() const
{
    return new Ifrit(*this);
}

void Ifrit::describeYourself()
{
    std::cout << "Ifrit:" << std::endl;
    Unit::describeYourself();
}

std::string Ifrit::getUnitInf()
{
    return "Ifrit:\n" + Unit::getUnitInf();
}

void Ifrit::closeTheRanks()
{

}

void Ifrit::fury()
{

}

Ifrit::~Ifrit()
{

}

eUnitsType Ifrit::getType()
{
    return INFANTRY;
}
