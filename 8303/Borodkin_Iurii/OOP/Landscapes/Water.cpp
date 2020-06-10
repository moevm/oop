#include "Water.h"

Water::Water() : Landscape(Qt::blue)
{}

bool Water::canStandUnit() const
{
    return true;
}

bool Water::canPlaceBuild() const
{
    return false;
}

bool Water::deathCell() const
{
    return false;
}

bool Water::canMove() const
{
    return false;
}

QBrush Water::brush() const
{
    return _brush;
}
