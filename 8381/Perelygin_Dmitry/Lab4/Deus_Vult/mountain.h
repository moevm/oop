#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#include "landscapes.h"
#include "unit.h"

class Mountian: public Landscapes
{

public:

    void apply_debuff(Unit* unit)override;


    Mountian()
    {
        debuff_range = 0;
        debuff_attack = 0;
        debuff_move = 2;
    }
};

#endif // MOUNTAIN_H
