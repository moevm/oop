#include "forest.h"


Forest::Forest()
{
    debuff_range = 2;
    debuff_attack = 2;
    debuff_move = 0;

}

void Forest::apply_debuff(Unit* unit)
{
    unit->set_d_range(debuff_range);
    unit->set_d_attack(debuff_attack);
    unit->set_d_move(debuff_move);
}
