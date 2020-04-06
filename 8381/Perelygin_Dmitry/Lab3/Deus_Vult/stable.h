#ifndef STABLE_H
#define STABLE_H
#include "neturalobjects.h"
#include "unit.h"

class Stable: public NeturalObjects
{

public:
    void operator+= (Unit& unit)override;

    Stable()
    {

    }
};


#endif // STABLE_H
