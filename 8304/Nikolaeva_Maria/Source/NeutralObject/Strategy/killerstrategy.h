#ifndef KILLERSTRATEGY_H
#define KILLERSTRATEGY_H

#include "strategy.h"


class KillerStrategy : public Strategy
{
public:
    KillerStrategy* clone() override;

    Unit* changeUnit(Unit *unit) override;
};

#endif // KILLERSTRATEGY_H
