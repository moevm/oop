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

bool Magician::meleeAttack(size_t x, size_t y) const
{
    return false;
}

void Magician::describeYourself()
{
    std::cout << "Magician:" << std::endl;
    Unit::describeYourself();
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

std::string Magician::getType()
{
    return "Wizard";
}
