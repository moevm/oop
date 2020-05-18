#ifndef FOREST_H
#define FOREST_H
#include "landscapes.h"
#include "unit.h"

class Forest: public Landscapes{
public:

    void apply_debuff(Unit* unit)override;

    Forest();

};

#endif // FOREST_H
