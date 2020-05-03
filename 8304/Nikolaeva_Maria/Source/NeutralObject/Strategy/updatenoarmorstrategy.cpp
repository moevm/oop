#include "updatenoarmorstrategy.h"


UpdateNoArmorStrategy* UpdateNoArmorStrategy::clone()
{ 
    UpdateNoArmorStrategy* updateNoArmorStrategy = new UpdateNoArmorStrategy();

    return updateNoArmorStrategy;
}


Unit* UpdateNoArmorStrategy::changeUnit(Unit *unit)
{
    unit->setArmor(new LightArmor());

    return unit;
}
