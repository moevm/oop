#ifndef ARMORY_H
#define ARMORY_H
#include "neturalobjects.h"
#include "unit.h"

class Armory: public NeturalObjects
{

public:
    void operator+= (Unit& unit)override;

    Armory()
    {

    }
};


#endif // ARMORY_H
