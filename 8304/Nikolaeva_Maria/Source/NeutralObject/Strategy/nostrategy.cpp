#include "nostrategy.h"


NoStrategy* NoStrategy::clone()
{
    NoStrategy* noStrategy = new NoStrategy();

    return noStrategy;
}

Unit* NoStrategy::changeUnit(Unit *unit)
{
    return unit;
}
