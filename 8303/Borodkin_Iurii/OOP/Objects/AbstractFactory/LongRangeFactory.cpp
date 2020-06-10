#include "LongRangeFactory.h"

Unit* LongRangeFactory::createArcher()
{
    return new Archer();
}

Unit* LongRangeFactory::createWizard()
{
    return new Wizard();
}
