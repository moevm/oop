#ifndef UPDATEHEAVYARMORSTRATEGY_H
#define UPDATEHEAVYARMORSTRATEGY_H

#include "strategy.h"


class UpdateHeavyArmorStrategy : public Strategy
{
public:
    UpdateHeavyArmorStrategy* clone() override;

    Unit* changeUnit(Unit *unit) override;
};

#endif // UPDATEHEAVYARMORSTRATEGY_H
