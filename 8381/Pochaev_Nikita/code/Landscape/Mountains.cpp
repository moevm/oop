#include "Mountains.h"

Mountains::Mountains()
{
    movingUnitsProhibition.emplace_back("Cannon fodder");
    movingUnitsProhibition.emplace_back("Infantry");
    movingUnitsProhibition.emplace_back("Cavalry");

    attackUnitsProhibition.emplace_back("Cannon fodder");
    attackUnitsProhibition.emplace_back("Cavalry");
}
