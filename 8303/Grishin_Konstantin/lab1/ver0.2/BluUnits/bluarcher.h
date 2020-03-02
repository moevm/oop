#ifndef BLUARCHER_H
#define BLUARCHER_H

#include "Units/range.h"


class BluArcher : public Archer
{
public:
    BluArcher(Cell *cell, RangeWeapon *weapon);
    void draw(sf::RenderTarget *target, int rect_size) override;
    Object* copy(CellGrid *grid) const override;
};

#endif // BLUARCHER_H
