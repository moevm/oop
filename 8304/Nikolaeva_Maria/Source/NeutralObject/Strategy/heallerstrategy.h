#ifndef HEALLERSTRATEGY_H
#define HEALLERSTRATEGY_H

#include "strategy.h"
#include "iostream"
constexpr size_t HEALLER_OBJECT_DH = 1;


class HeallerStrategy : public Strategy
{
public:
    HeallerStrategy* clone() override;

    Unit* changeUnit(Unit *unit) override;
};

#endif // HEALLERSTRATEGY_H
