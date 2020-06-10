#ifndef LAVA_H
#define LAVA_H
#include "Landscape.h"

class Lava : public Landscape
{
public:
    Lava();
    bool canStandUnit() const override;
    bool canPlaceBuild() const override;
    bool deathCell() const override;
    bool canMove() const override;
    QBrush brush() const override;
};

#endif // LAVA_H
