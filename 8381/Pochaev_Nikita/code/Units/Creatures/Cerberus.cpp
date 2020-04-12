#include "Cerberus.h"

Cerberus::Cerberus()
{
    health = 25;
    armor = 5;
    meleeAttackStrength = 12;
    actionTokens = 2;
    movementRange = CERBERUS_MOVEMENT_RANGE;
}

Cerberus::Cerberus(std::string inputName) : Cerberus()
{
    name = std::move(inputName);
}

Cerberus* Cerberus::clone() const
{
    return new Cerberus(*this);
}

void Cerberus::describeYourself()
{
    std::cout << "Cerberus:" << std::endl;
    Unit::describeYourself();
}

std::string Cerberus::getUnitInf()
{
    return "Cerberus:\n" + Unit::getUnitInf();
}

void Cerberus::postMortem()
{

}

void Cerberus::armament()
{

}

Cerberus::~Cerberus()
{

}

eUnitsType Cerberus::getType()
{
    return CAVALRY;
}
