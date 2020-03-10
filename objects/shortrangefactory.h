#ifndef SHORTRANGEFACTORY_H
#define SHORTRANGEFACTORY_H
#include "objects/SwordsMan.h"
#include "objects/SpearMan.h"

class ShortRangeFactory
{
public:
    Object* createSwordsMan();
    Object* createSpearMan();
};

#endif // SHORTRANGEFACTORY_H
