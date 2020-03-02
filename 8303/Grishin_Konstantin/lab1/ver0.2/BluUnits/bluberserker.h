#ifndef BLUNUKER_H
#define BLUNUKER_H

#include "Units/nuker.h"

class BluBerserker : public Berserker
{
public:
    BluBerserker(Cell *cell, NukerWeapon *weapon);
    void draw(sf::RenderTarget *target, int rect_size) override;
    Object* copy(CellGrid *field) const override;
};

#endif // BLUNUKER_H
