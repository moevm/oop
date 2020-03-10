#ifndef UNITSFACTORY_H
#define UNITSFACTORY_H
#include "objects/Object.h"

class UnitsFactory
{
public:
    virtual Object* createShortRange() = 0;
    virtual Object* createLongRange() = 0;
    virtual Object* createRider() = 0;
    virtual ~UnitsFactory() = default;
};

#endif // UNITSFACTORY_H
