
#ifndef OOP_LAB1_ARCHER_H
#define OOP_LAB1_ARCHER_H

#include "Bow.h"
#include "Unit.h"

class Archer: public Unit{

public:
    Archer(){

        weapon = Bow();

    }

};

#endif //OOP_LAB1_ARCHER_H
