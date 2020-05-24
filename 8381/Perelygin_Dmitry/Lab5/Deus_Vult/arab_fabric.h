#ifndef ARAB_FABRIC_H
#define ARAB_FABRIC_H
#include "fabrics.h"



class Arab_fabric: public Fabrics{
    public:
    Arab_fabric() = default;

// Реализация параметризированного фабричного метода
Unit* createWarrior ( Warrior_ID id, int new_name, class Field *new_field, class Base* new_base )override;
};

#endif // ARAB_FABRIC_H
