
#ifndef OOP_LAB1_ICEMAGE_H
#define OOP_LAB1_ICEMAGE_H

#include "Wizard.h"
#include "IceStorm.h"

class IceMage: public Wizard{

public:

    IceMage(): Wizard(){

        weapon =IceStorm();
        health = 90;

    }

};


#endif //OOP_LAB1_ICEMAGE_H
