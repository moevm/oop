#ifndef UPDATELIGHTARMORSTRATEGY_H
#define UPDATELIGHTARMORSTRATEGY_H

#include "strategy.h"


class UpdateLightArmorStrategy : public Strategy
{
public:
    UpdateLightArmorStrategy* clone() override;

    Unit* changeUnit(Unit *unit) override;
};

#endif // UPDATELIGHTARMORSTRATEGY_H
