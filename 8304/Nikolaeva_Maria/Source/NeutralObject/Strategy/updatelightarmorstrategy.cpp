#include "updatelightarmorstrategy.h"


UpdateLightArmorStrategy* UpdateLightArmorStrategy::clone()
{ 
    UpdateLightArmorStrategy* updateLightArmorStrategy = new UpdateLightArmorStrategy();

    return updateLightArmorStrategy;
}


Unit* UpdateLightArmorStrategy::changeUnit(Unit* unit)
{
    unit->setArmor(new HeavyArmor());

    return unit;
}
