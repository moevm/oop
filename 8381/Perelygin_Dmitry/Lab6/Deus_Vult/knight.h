#ifndef KNIGHT_H
#define KNIGHT_H
#include "cavalry.h"
class Knight: public Cavalry{
    public:
    Knight(int new_name, class Field *new_field, class Base *new_base)
    {
         field = new_field;
         name = new_name;
         base = new_base;
         hp = 150;
         armor = 20;
         attack = 30;
         move = 7;
         range = 1;
         cost = 300;
    }
};
#endif // KNIGHT_H
