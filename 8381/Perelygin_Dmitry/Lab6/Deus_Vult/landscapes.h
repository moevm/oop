#ifndef LANDSCAPES_H
#define LANDSCAPES_H


class Unit;

class Landscapes
{
protected:
    int debuff_range = 0;
    int debuff_attack = 0;
    int debuff_move = 0;

public:

    virtual void apply_debuff(Unit* unit) = 0;

    Landscapes()=default;
};

#endif // LANDSCAPES_H
