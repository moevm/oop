#ifndef NOSTRATEGY_H
#define NOSTRATEGY_H

#include "strategy.h"


class NoStrategy : public Strategy
{
public:
    NoStrategy* clone() override;

    Unit* changeUnit(Unit *unit) override;
};

#endif // NOSTRATEGY_H
