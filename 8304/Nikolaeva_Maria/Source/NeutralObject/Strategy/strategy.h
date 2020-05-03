#ifndef STRATEGY_H
#define STRATEGY_H

#include "Unit/unit.h"


class Strategy
{
public:
    virtual ~Strategy() = default;

    virtual Unit* changeUnit(Unit* unit) = 0;

    virtual Strategy* clone() = 0;
};

#endif // STRATEGY_H
