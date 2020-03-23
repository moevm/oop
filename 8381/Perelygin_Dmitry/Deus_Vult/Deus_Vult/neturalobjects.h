#ifndef NETURALOBJECTS_H
#define NETURALOBJECTS_H
#include "unit.h"

class NeturalObjects
{
protected:
    int x;

public:
    virtual void operator+= (Unit& unit) = 0;

    NeturalObjects() = default;

    ~NeturalObjects() = default;
};

#endif // NETURALOBJECTS_H
