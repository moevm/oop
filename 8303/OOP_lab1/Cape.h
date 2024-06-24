
#ifndef OOP_LAB1_CAPE_H
#define OOP_LAB1_CAPE_H

#include "Armor.h"

class Cape: public Armor{

public:
    Cape(){

        damageResistance = 1;
        type = ArmorType::LIGHT;

    }

};


#endif //OOP_LAB1_CAPE_H
