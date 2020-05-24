#ifndef ARAB_H
#define ARAB_H
#include "infantry.h"
class Arab: public Infantry{
    public:
    Arab(int new_name, class Field *new_field, class Base *new_base)
    {
        field = new_field;
        name = new_name;
        base = new_base;
        type = 4;
        hp = 80;
        armor = 10;
        attack = 35;
        move = 4;
        range = 1;
        cost = 80;
    }
};
#endif // ARAB_H
