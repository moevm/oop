#include "killerstrategy.h"


KillerStrategy* KillerStrategy::clone()
{  
    KillerStrategy* killerStrategy = new KillerStrategy();

    return killerStrategy;
}


Unit* KillerStrategy::changeUnit(Unit *unit)
{
   unit->toHurt(unit->getHealth());
    return unit;
}
