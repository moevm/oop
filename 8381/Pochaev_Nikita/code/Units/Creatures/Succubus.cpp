#include "Succubus.h"

Succubus::Succubus()
{
    health = 15;
    armor = 0;
    meleeAttackStrength = 3;
    actionTokens = 2;
    movementRange = SUCCUBUS_MOVEMENT_RANGE;
}

Succubus::Succubus(std::string inputName) : Succubus()
{
    name = std::move(inputName);
}

Succubus* Succubus::clone() const
{
    return new Succubus(*this);
}

bool Succubus::meleeAttack(size_t x, size_t y) const
{
    return false;
}

void Succubus::describeYourself()
{
    std::cout << "Succubus:" << std::endl;
    Unit::describeYourself();
}

void Succubus::shot()
{

}

void Succubus::canopyShooting()
{

}

Succubus::~Succubus()
{

}

std::string Succubus::getType()
{
    return "Shooter";
}
