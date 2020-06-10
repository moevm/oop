#include "Rock.h"

Rock::Rock() : Landscape(Qt::darkGreen)
{}

bool Rock::canStandUnit() const
{
    return false;
}

bool Rock::canPlaceBuild() const
{
    return false;
}

bool Rock::deathCell() const
{
    return false;
}

bool Rock::canMove() const
{
    return false;
}

QBrush Rock::brush() const
{
    return _brush;
}
