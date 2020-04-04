#pragma once

#include "Landscape/Landscape.h"


class Mountain : public Landscape
{
public:
    Mountain(Point point);
    bool movementAccess() override;
    uint8_t getObjectType() override;
};
