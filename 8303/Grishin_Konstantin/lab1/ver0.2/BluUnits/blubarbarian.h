#ifndef BLUBARBARIAN_H
#define BLUBARBARIAN_H

#include "Units/melee.h"

class BluBarbarian : public Barbarian
{
public:
    BluBarbarian(Cell *cell, MeleeWeapon *weapon);
    void draw(sf::RenderTarget *target, int rect_size) override;
    Object* copy(CellGrid *field) const override;
};

#endif // BLUBARBARIAN_H
