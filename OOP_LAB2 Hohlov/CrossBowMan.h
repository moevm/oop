
#ifndef OOP_LAB1_CROSSBOWMAN_H
#define OOP_LAB1_CROSSBOWMAN_H
#include "Archer.h"
#include "LaminarArmor.h"

class CrossBowMan: public Archer{

public:

    CrossBowMan(): Archer( *ArmorFlyWeight::getFlyWeight<LaminarArmor>(), 100){}

};
#endif //OOP_LAB1_CROSSBOWMAN_H
