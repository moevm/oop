#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "Unit/unit.h"

#include "IDrawable.h"


class Landscape : public IDrawable
{
public:
    virtual ~Landscape() = default;

    virtual void hurtUnit(Unit* unit) = 0;
    virtual bool canMove(Unit* unit) = 0;
    virtual Landscape* clone() = 0;
};

#endif // LANDSCAPE_H
