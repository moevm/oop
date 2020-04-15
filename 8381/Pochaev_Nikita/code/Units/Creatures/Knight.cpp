#include "Knight.h"

Knight::Knight()
{
    health = 20;
    armor = 10;
    meleeAttackStrength = 10;
    actionTokens = 3;
    movementRange = KNIGHT_MOVEMENT_RANGE;
}

Knight::Knight(std::string inputName) : Knight()
{
    name = std::move(inputName);
}

Knight* Knight::clone() const
{
    return new Knight(*this);
}

void Knight::describeYourself()
{
    std::cout << "Knight:" << std::endl;
    Unit::describeYourself();
}

std::string Knight::getUnitInf()
{
    return "Knight:\n" + Unit::getUnitInf();
}

void Knight::postMortem()
{

}

void Knight::armament()
{

}

Knight::~Knight()
{

}

eUnitsType Knight::getType()
{
    return CAVALRY;
}
