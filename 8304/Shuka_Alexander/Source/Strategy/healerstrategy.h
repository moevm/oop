#ifndef HEALERSTRATEGY_H
#define HEALERSTRATEGY_H

#include "strategy.h"


class HealerStrategy : public Strategy
{
public:
    virtual void changeUnit(std::shared_ptr<unit::Unit> unit) const override;

    virtual std::shared_ptr<Strategy> clone() const override;
};

#endif // HEALERSTRATEGY_H
