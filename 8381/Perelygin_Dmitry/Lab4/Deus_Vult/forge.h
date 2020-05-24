#ifndef FORGE_H
#define FORGE_H
#include "neturalobjects.h"
#include "unit.h"

class Forge: public NeturalObjects
{

public:
    void operator+= (Unit& unit)override;

    Forge()
    {

    }
};

#endif // FORGE_H
