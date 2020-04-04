#pragma once

#include "ILandscape.h"


class Landscape : public ILandscape
{
public:
    Landscape(Point point);
    Point getPoint() override;
    int8_t getMovementCost() override;

protected:
    Point point;
    int8_t movementCost;
};
