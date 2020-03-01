#ifndef INFANTRYUNIT_H
#define INFANTRYUNIT_H

#include "unit.h"


class InfantryUnit : public Unit
{
public:
    explicit InfantryUnit() = default;
    virtual ~InfantryUnit() = default;

    bool move(int dx, int dy) override;
;
    bool isFlying() override;
};

#endif // INFANTRYUNIT_H
