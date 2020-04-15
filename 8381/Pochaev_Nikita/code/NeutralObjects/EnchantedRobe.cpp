#include "EnchantedRobe.h"

void EnchantedRobe::operator+=(const std::shared_ptr<Unit> &unit)
{
    unit->setArmorBoost(ENCHANTED_ROBE_BOOST);
}

std::string EnchantedRobe::getNameOfNeutralObject()
{
    return "Enchanted robe";
}
