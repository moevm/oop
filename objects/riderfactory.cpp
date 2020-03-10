#include "riderfactory.h"

Object* RiderFactory::createPanzer()
{
    return new Panzer();
}

Object* RiderFactory::createCentaur()
{
    return new Centaur();
}
