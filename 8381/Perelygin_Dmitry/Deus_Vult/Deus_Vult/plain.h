#ifndef PLAIN_H
#define PLAIN_H
#include "landscapes.h"
#include "unit.h"

class Plain: public Landscapes
{


public:

    void apply_debuff(Unit* unit)override;

    Plain()
    {
        debuff_range = 0;
        debuff_attack = 0;
        debuff_move = 0;

    }
};

#endif // PLAIN_H
