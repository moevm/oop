#ifndef REDBARBARIAN_H
#define REDBARBARIAN_H

#include "Units/melee.h"

class RedBarbarian : public Barbarian
{
public:
    RedBarbarian(Cell *cell, MeleeWeapon *weapon);
    void draw(sf::RenderTarget *target, int rect_size) override;
    Object* copy(CellGrid *field) const override;
};

#endif // REDBARBARIAN_H
