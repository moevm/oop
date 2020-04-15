#include "Mountains.h"

Mountains::Mountains()
{
    movingUnitsProhibition.emplace_back(eUnitsType::CANNON_FODDER);
    movingUnitsProhibition.emplace_back(eUnitsType::INFANTRY);
    movingUnitsProhibition.emplace_back(eUnitsType::CAVALRY);

    attackUnitsProhibition.emplace_back(eUnitsType::CANNON_FODDER);
    attackUnitsProhibition.emplace_back(eUnitsType::CAVALRY);
}

std::string Mountains::getNameOfLandscape()
{
    return "Mountains";
}
