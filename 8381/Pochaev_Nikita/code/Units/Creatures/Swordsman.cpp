#include "Swordsman.h"

Swordsman::Swordsman()
{
    health = 15;
    armor = 10;
    meleeAttackStrength = 7;
    actionTokens = 1;
    movementRange = SWORDSMAN_MOVEMENT_RANGE;
}

Swordsman::Swordsman(std::string inputName) : Swordsman()
{
    name = std::move(inputName);
}

Swordsman* Swordsman::clone() const
{
    return new Swordsman(*this);
}

void Swordsman::describeYourself()
{
    std::cout << "Swordsman:" << std::endl;
    Unit::describeYourself();
}

std::string Swordsman::getUnitInf()
{
    return "Swordsman:\n" + Unit::getUnitInf();
}

void Swordsman::closeTheRanks()
{

}

void Swordsman::fury()
{

}

Swordsman::~Swordsman()
{

}

eUnitsType Swordsman::getType()
{
    return INFANTRY;
}
