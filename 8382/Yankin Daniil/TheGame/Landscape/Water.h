#pragma once

#include "Landscape/Landscape.h"


class Water : public Landscape
{
public:
    Water(Point point);
    bool movementAccess() override;
    uint8_t getObjectType() override;
};
