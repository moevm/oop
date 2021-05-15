#ifndef UNITSGROUP_H
#define UNITSGROUP_H

#include <vector>

#include "Unit/Unit.h"

class UnitsGroup: public Unit
{
public:
    std::vector<Unit*> unitsGroup;

    void addUnit(Unit* unit);
    void removeUnit(Unit* unit);
    void print();

    size_t size() { return unitsGroup.size(); }

    char type() { return 'G'; } // Group
};

#endif // UNITSGROUP_H
