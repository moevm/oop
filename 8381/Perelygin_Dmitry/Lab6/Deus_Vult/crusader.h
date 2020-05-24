#ifndef CRUSADER_H
#define CRUSADER_H
#include "infantry.h"
class Crusader: public Infantry{
    public:
    Crusader(int new_name, class Field *new_field, class Base *new_base)
    {
        field = new_field;
        name = new_name;
        base = new_base;
        type = 1;
        hp = 100;
        armor = 15;
        attack = 40;
        move = 2;
        range = 1;
        cost = 100;
    }
};
#endif // CRUSADER_H
