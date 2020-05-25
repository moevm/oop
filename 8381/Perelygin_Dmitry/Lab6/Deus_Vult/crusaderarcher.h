#ifndef CRUSADERARCHER_H
#define CRUSADERARCHER_H
#include "shooter.h"
class CrusaderArcher: public Shooter{
    public:
    CrusaderArcher(int new_name, class Field *new_field, class Base *new_base)
    {
         field = new_field;
         name = new_name;
         base = new_base;
         type = 3;
         hp = 70;
         armor = 10;
         attack = 20;
         move = 4;
         range = 5;
         cost = 80;
    }
};
#endif // CRUSADERARCHER_H
