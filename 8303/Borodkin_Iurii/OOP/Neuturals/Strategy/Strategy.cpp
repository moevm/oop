#include "Strategy.h"

template <class TPack>
void Strategy<TPack>::useStrategy(Object* unit, Pack** pack)
{
    this->buff(unit, pack);
}
