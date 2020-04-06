#include "leaf.h"

string Leaf::nameUnit(Unit *unit)
{
    return unit->getName();
}

string Leaf::characteristicUnit(Unit *unit)
{
    return unit->characteristic();
}
