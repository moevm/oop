
#ifndef OOP_LAB1_IRONARMOR_H
#define OOP_LAB1_IRONARMOR_H
#include <climits>
#include "Armor.h"

class IronArmor: public Armor{

public:
    IronArmor(){

        damageResistance = INT_MAX;
        type = ArmorType::HEAVY;

    }

};
#endif //OOP_LAB1_IRONARMOR_H
