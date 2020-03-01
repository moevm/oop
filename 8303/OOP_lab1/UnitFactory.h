
#ifndef OOP_LAB1_UNITFACTORY_H
#define OOP_LAB1_UNITFACTORY_H

#include "Unit.h"

class UnitFactory {

public:
    virtual Unit* createFirst()=0;
    virtual Unit* createSecond()=0;

};

#endif //OOP_LAB1_UNITFACTORY_H
