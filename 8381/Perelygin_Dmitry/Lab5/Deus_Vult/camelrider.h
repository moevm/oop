#ifndef CAMELRIDER_H
#define CAMELRIDER_H
#include "cavalry.h"
class CamelRider: public Cavalry{
    public:
    CamelRider(int new_name, class Field *new_field, class Base *new_base)
    {
        field = new_field;
        name = new_name;
        base = new_base;
        type = 5;
        hp = 130;
        armor = 15;
        attack = 35;
        move = 10;
        range = 1;
        cost = 200;
    }
};
#endif // CAMELRIDER_H
