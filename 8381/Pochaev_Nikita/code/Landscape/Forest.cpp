#include "Forest.h"

Forest::Forest()
{
    movingUnitsProhibition.emplace_back(eUnitsType::CAVALRY);
    actionTokensUnitsBoost.emplace_back(eUnitsType::CANNON_FODDER);
    attackUnitsProhibition.emplace_back(eUnitsType::SHOOTER);
}

std::string Forest::getNameOfLandscape()
{
    return "Forest";
}
