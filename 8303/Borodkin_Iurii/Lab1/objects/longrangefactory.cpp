#include "longrangefactory.h"

Object* LongRangeFactory::createArcher()
{
    return new Archer();
}

Object* LongRangeFactory::createWizard()
{
    return new Wizard();
}
