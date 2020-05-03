 #include "updateheavyarmorstrategy.h"


UpdateHeavyArmorStrategy* UpdateHeavyArmorStrategy::clone()
{
    UpdateHeavyArmorStrategy* updateHeavyArmorStrategy = new UpdateHeavyArmorStrategy();

    return updateHeavyArmorStrategy;
}


Unit* UpdateHeavyArmorStrategy::changeUnit(Unit* unit)
{
   return unit;
}
