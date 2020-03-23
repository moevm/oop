#ifndef LEAF_H
#define LEAF_H

#include "unit.h"
#include <list>
class Leaf : BaseComponent
{
public:
    string nameUnit(Unit *unit);
    string characteristicUnit(Unit *unit);
};

#endif // LEAF_H
