
#ifndef OOP_LAB1_FIREMAGE_H
#define OOP_LAB1_FIREMAGE_H

#include "Wizard.h"
#include "Fireball.h"

class FireMage: public Wizard{

public:

    FireMage(): Wizard(*WeaponFlyWeight::getFlyWeight<Fireball>(), 100){}

};

#endif //OOP_LAB1_FIREMAGE_H
