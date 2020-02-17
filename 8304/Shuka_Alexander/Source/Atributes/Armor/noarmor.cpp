#include "noarmor.h"


NoArmor::NoArmor()
{
    resistance = NO_ARMOR;
}


double NoArmor::getResistance() const
{
    return resistance;
}


NoArmor::NoArmor(const NoArmor& armor)
{
    this->doCopy(armor);
}


std::unique_ptr<Armor> NoArmor::clone()
{
    std::unique_ptr<Armor> armor(new NoArmor(*this));
    return armor;
}


NoArmor& NoArmor::operator=(const NoArmor& armor)
{
    if (this == &armor) {
        return *this;
    }

    this->doCopy(armor);

    return *this;
}
