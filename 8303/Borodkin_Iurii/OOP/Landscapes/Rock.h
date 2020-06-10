#ifndef ROCK_H
#define ROCK_H
#include "Landscape.h"

class Rock : public Landscape
{
public:
    Rock();
    bool canStandUnit() const override;
    bool canPlaceBuild() const override;
    bool deathCell() const override;
    bool canMove() const override;
    QBrush brush() const override;
};

#endif // ROCK_H
