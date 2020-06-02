
#ifndef OOP_LAB1_ICEMAGE_H
#define OOP_LAB1_ICEMAGE_H

#include "Wizard.h"
#include "IceStorm.h"

class IceMage: public Wizard{

public:

    IceMage(): Wizard(*WeaponFlyWeight::getFlyWeight<IceStorm()>(), 7){}

};
#endif //OOP_LAB1_ICEMAGE_H
