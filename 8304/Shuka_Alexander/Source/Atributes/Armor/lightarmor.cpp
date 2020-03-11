#include "lightarmor.h"


LightArmor::LightArmor()
{
    resistance = LIGHT_ARMOR;
}


double LightArmor::getResistance() const
{
    return resistance;
}


std::unique_ptr<Armor> LightArmor::clone()
{
    std::unique_ptr<Armor> armor(new LightArmor(*this));
    return armor;
}


LightArmor::LightArmor(const LightArmor& armor)
{
    this->doCopy(armor);
}


LightArmor& LightArmor::operator=(const LightArmor& armor)
{
    if (this == &armor) {
        return *this;
    }

    this->doCopy(armor);

    return *this;
}
