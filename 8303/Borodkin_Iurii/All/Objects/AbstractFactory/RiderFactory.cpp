#include "RiderFactory.h"

Unit* RiderFactory::createPanzer()
{
    return new Panzer();
}

Unit* RiderFactory::createCentaur()
{
    return new Centaur();
}
