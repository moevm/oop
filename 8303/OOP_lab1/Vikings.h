

#ifndef OOP_LAB1_VIKINGS_H
#define OOP_LAB1_VIKINGS_H

#include "Unit.h"
#include "IronArmor.h"

class Viking: public Unit {

public:

    Viking() {

        armor = IronArmor();

    }

};

#endif //OOP_LAB1_VIKINGS_H
