#ifndef COMPOSIT_H
#define COMPOSIT_H
#include <vector>
#include "units.h"

class Composit: public Unit
{
public:
    std::vector<Unit*> arrUnits;
    void add_unit(Unit* unit);
    void remove_unit(Unit* unit);
};

#endif // COMPOSIT_H
