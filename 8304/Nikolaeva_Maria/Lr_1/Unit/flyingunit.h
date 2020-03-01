#ifndef FLYINGUNIT_H
#define FLYINGUNIT_H

#include "unit.h"


class FlyingUnit : public Unit
{
public:
    explicit FlyingUnit() = default;
    virtual ~FlyingUnit() = default;

    bool move(int dx, int dy) override;

    bool isFlying() override;
};

#endif // FLYINGUNIT_H
