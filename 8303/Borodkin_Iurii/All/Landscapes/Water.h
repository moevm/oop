#ifndef WATER_H
#define WATER_H
#include "Landscape.h"

class Water : public Landscape
{
public:
    Water();
    bool canStandUnit() const override;
    bool canPlaceBuild() const override;
    bool deathCell() const override;
    bool canMove() const override;
    QBrush brush() const override;
};

#endif // WATER_H
