#ifndef REDBERSERKER_H
#define REDBERSERKER_H

#include "Units/nuker.h"

class RedBerserker : public Berserker
{
public:
    RedBerserker(Cell *cell, NukerWeapon *weapon);
    void draw(sf::RenderTarget *target, int rect_size) override;
    Object* copy(CellGrid *field) const override;
};

#endif // REDBERSERKER_H
