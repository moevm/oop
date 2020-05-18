#ifndef WELL_H
#define WELL_H
#include "neturalobjects.h"
#include "unit.h"

class Well: public NeturalObjects
{

public:
    void operator+= (Unit& unit)override;

    Well()
    {

    }
    ~Well();
};

#endif // WELL_H
