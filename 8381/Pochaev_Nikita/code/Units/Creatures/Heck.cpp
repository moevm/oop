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

bool Heck::meleeAttack(size_t x, size_t y) const
{
    return false;
}

void Heck::describeYourself()
{
    std::cout << "Heck:" << std::endl;
    Unit::describeYourself();
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

std::string Heck::getType()
{
    return "Cannon fodder";
}
