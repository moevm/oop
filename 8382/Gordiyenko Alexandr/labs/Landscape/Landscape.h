#ifndef LABS_LANDSCAPE_H
#define LABS_LANDSCAPE_H

#include "../Units/Unit.h"
#include "../extra1/UnitCreator.h"

class Landscape {
public:
    virtual bool canMove(Unit *unit) = 0;
    virtual char typeLandscape() = 0;

    virtual ~Landscape() {}
};

#endif //LABS_LANDSCAPE_H
