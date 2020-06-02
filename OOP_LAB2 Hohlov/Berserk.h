
#ifndef OOP_LAB1_BERSERK_H
#define OOP_LAB1_BERSERK_H

#include "Vikings.h"
#include "Axe.h"

class Berserk: public Viking{

public:

    Berserk(): Viking(*WeaponFlyWeight::getFlyWeight<Axe>(), 50){}
};

#endif //OOP_LAB1_BERSERK_H
