#include "ShortRangeFactory.h"

Unit* ShortRangeFactory::createSwordsMan()
{
    return new SwordsMan;
}

Unit* ShortRangeFactory::createSpearMan()
{
    return new SpearMan;
}
