#include "neutralobject.hpp"

void NeutralObject::operator[](std::shared_ptr<Unit> unit)
{
    selectLogic(unit);
    strategyPattern->updateUnit(unit);
}
