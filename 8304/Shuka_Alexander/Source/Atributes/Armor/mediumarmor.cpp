#include "mediumarmor.h"


MediumArmor::MediumArmor()
{
    resistance = MEDIUM_ARMOR;
}


double MediumArmor::getResistance() const
{
    return resistance;
}


MediumArmor::MediumArmor(const MediumArmor& armor)
{
    this->doCopy(armor);
}


std::unique_ptr<Armor> MediumArmor::clone()
{
    std::unique_ptr<Armor> armor(new MediumArmor(*this));
    return armor;
}


MediumArmor& MediumArmor::operator=(const MediumArmor& armor)
{
    if (this == &armor) {
        return *this;
    }

    this->doCopy(armor);

    return *this;
}
