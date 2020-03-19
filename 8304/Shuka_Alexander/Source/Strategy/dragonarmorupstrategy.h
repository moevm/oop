#ifndef DRAGONARMORUPSTRATEGY_H
#define DRAGONARMORUPSTRATEGY_H

#include "strategy.h"

#include "Factory/ArmorFactory/heavyarmorfactory.h"


class DragonArmorUpStrategy : public Strategy
{
public:
    virtual void changeUnit(std::shared_ptr<unit::Unit> unit) const override;

    virtual std::shared_ptr<Strategy> clone() const override;
};

#endif // DRAGONARMORUPSTRATEGY_H
