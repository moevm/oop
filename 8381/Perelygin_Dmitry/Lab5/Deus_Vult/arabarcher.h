#ifndef ARABARCHER_H
#define ARABARCHER_H
#include "shooter.h"
class ArabArcher: public Shooter{
    public:
    ArabArcher(int new_name, class Field *new_field, class Base *new_base)
    {
        field = new_field;
        name = new_name;
        base = new_base;
        type = 6;
        hp = 70;
        armor = 5;
        attack = 15;
        move = 5;
        range = 5;
        cost = 60;
    }
};
#endif // ARABARCHER_H
