#include "neutralobject.h"

using namespace unit;


void NeutralObject::operator[](std::shared_ptr<Unit> unit)
{
    selectStrategy(unit);
    strategy->changeUnit(unit);
}
