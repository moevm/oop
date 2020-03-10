#include "shortrangefactory.h"

Object* ShortRangeFactory::createSwordsMan()
{
    return new SwordsMan;
}

Object* ShortRangeFactory::createSpearMan()
{
    return new SpearMan;
}
