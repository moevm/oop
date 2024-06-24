
#ifndef OOP_LAB1_SNIPER_H
#define OOP_LAB1_SNIPER_H

#include "Archer.h"
#include "LeatherArmor.h"

class Sniper: public Archer{

public:

    Sniper(): Archer( *ArmorFlyWeight::getFlyWeight<LeatherArmor>(), 100){}

};

#endif //OOP_LAB1_SNIPER_H
