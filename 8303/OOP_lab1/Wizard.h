
#ifndef OOP_LAB1_WIZARD_H
#define OOP_LAB1_WIZARD_H


#include "Unit.h"
#include "Cape.h"
#include "Fireball.h"

class Wizard: public Unit{

public:

    Wizard(){

        armor = Cape();

    }

};


#endif //OOP_LAB1_WIZARD_H
