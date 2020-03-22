#include "Forest.h"

Forest::Forest()
{
    movingUnitsProhibition.emplace_back("Cavalry");
    actionTokensUnitsBoost.emplace_back("Cannon fodder");
    attackUnitsProhibition.emplace_back("Shooter");
}
