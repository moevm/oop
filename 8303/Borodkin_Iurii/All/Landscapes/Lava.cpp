#include "Lava.h"

Lava::Lava() : Landscape(Qt::red)
{}

bool Lava::canStandUnit() const
{
    return true;
}

bool Lava::canPlaceBuild() const
{
    return false;
}

bool Lava::deathCell() const
{
    return true;
}

bool Lava::canMove() const
{
    return true;
}

QBrush Lava::brush() const
{
    return _brush;
}
