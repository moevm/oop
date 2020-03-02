#ifndef REDARCHER_H
#define REDARCHER_H

#include "Units/range.h"

class RedArcher : public Archer
{
public:
    RedArcher(Cell *cell, RangeWeapon *weapon);
    void draw(sf::RenderTarget *target, int rect_size) override;
    Object* copy(CellGrid *field) const override;
};

#endif // REDARCHER_H
