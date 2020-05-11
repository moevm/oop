#include "mountain.h"

void Mountian::apply_debuff(Unit* unit)
{
    unit->set_d_range(debuff_range);
    unit->set_d_attack(debuff_attack);
    unit->set_d_move(debuff_move);


}
