#pragma once

#include "Landscape.h"


class LandscapeProxy : public ILandscape
{
public:
    LandscapeProxy(Landscape* landscape);
    ~LandscapeProxy();

    uint8_t getObjectType() override;
    Point getPoint() override;
    bool movementAccess() override;
    int8_t getMovementCost() override;

private:
    void log();

    Landscape* landscape;
};
