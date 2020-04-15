#pragma once

#include "Object/Object.h"


class ILandscape : public Object
{
public:
    uint8_t getGroupType() override;
    virtual bool movementAccess() = 0;
    virtual int8_t getMovementCost() = 0;
};
