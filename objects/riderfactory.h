#ifndef RIDERFACTORY_H
#define RIDERFACTORY_H

#include "objects/Panzer.h"
#include "objects/Centaur.h"

class RiderFactory
{
public:
    Object* createPanzer();
    Object* createCentaur();
};

#endif // RIDERFACTORY_H
