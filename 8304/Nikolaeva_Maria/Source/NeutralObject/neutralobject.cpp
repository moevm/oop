#include "neutralobject.h"


Unit* NeutralObject::operator()(Unit* unit)
{
    selectStrategy(unit);

    return strategy->changeUnit(unit);
}
