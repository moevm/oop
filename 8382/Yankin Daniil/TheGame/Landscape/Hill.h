#pragma once

#include "Landscape/Landscape.h"


class Hill : public Landscape
{
public:
    Hill(Point point);
    bool movementAccess() override;
    uint8_t getObjectType() override;
};
