#include "gamecell.h"


GameCell::GameCell(Object* &obj, QRectF rect, QPen pen) : obj(obj), rectf(rect), pen(pen)
{}

bool GameCell::canStandUnit() const
{
    return landscape->canStandUnit() && obj == nullptr;
}

bool GameCell::canMove() const
{
    return landscape->canMove() && obj != nullptr;
}

bool GameCell::canPlaceBuild() const
{
    return landscape->canPlaceBuild() && obj == nullptr;
}

bool GameCell::empty() const
{
    return obj == nullptr;
}

GameCell::~GameCell()
{}
