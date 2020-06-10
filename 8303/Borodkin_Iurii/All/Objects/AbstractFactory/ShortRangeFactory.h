#ifndef SHORTRANGEFACTORY_H
#define SHORTRANGEFACTORY_H
#include "../Units/SwordsMan.h"
#include "../Units/SpearMan.h"

class ShortRangeFactory
{
public:
    Unit* createSwordsMan();
    Unit* createSpearMan();
};

#endif // SHORTRANGEFACTORY_H
