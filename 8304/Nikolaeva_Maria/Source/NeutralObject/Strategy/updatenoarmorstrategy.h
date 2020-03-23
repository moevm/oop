#ifndef UPDATENOARMORSTRATEGY_H
#define UPDATENOARMORSTRATEGY_H

#include "strategy.h"


class UpdateNoArmorStrategy : public Strategy
{
public:
    UpdateNoArmorStrategy* clone() override;

    Unit* changeUnit(Unit *unit) override;
};

#endif // UPDATENOARMORSTRATEGY_H
