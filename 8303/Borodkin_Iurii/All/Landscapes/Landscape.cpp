#include "Landscape.h"

Landscape::Landscape(QBrush brush) : _brush(brush)
{}

void Landscape::kill(Object *&unit)
{
    delete unit;
    unit = nullptr;
}

bool Landscape::canStandUnit() const
{
    return true;
}

bool Landscape::canPlaceBuild() const
{
    return true;
}

bool Landscape::deathCell() const
{
    return false;
}

bool Landscape::canMove() const
{
    return true;
}

QBrush Landscape::brush() const
{
    return _brush;
}
