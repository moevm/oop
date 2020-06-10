#ifndef STRATEGY_H
#define STRATEGY_H
#include "Objects/Units/Unit.h"
#include "Neuturals/Packs.h"


template <class TPack>
class Strategy : public TPack
{
public:
    void useStrategy(Object*, Pack**);
};

template class Strategy <ArmorStrategy>;

template class Strategy <ManaStrategy>;

template class Strategy <DamageStrategy>;

template class Strategy <HealthStrategy>;

#endif // STRATEGY_H
