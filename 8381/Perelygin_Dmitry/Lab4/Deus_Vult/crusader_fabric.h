#ifndef CRUSADER_FABRIC_H
#define CRUSADER_FABRIC_H
#include "fabrics.h"
#include <iostream>
#include <vector>


class Crusader_fabric: public Fabrics{
    public:

    Crusader_fabric() = default;

    // Реализация параметризированного фабричного метода
    Unit* createWarrior ( Warrior_ID id,int new_name, class Field *new_field, class Base* new_base )override;

};


#endif // CRUSADER_FABRIC_H
