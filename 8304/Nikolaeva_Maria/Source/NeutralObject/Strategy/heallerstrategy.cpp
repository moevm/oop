#include "heallerstrategy.h"


HeallerStrategy* HeallerStrategy::clone()
{
    HeallerStrategy* heallerStrategy = new HeallerStrategy();

    return heallerStrategy;
}


Unit* HeallerStrategy::changeUnit(Unit *unit)
{
    unit->toHurt(-HEALLER_OBJECT_DH);

    return unit;
}
