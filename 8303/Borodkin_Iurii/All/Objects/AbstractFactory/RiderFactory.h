#ifndef RIDERFACTORY_H
#define RIDERFACTORY_H

#include "../Units/Panzer.h"
#include "../Units/Centaur.h"

class RiderFactory
{
public:
    Unit* createPanzer();
    Unit* createCentaur();
};

#endif // RIDERFACTORY_H
