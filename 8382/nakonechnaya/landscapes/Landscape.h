#ifndef OOP_LANDSCAPE_H
#define OOP_LANDSCAPE_H
#include "../Objects/units/Unit.h"

enum Land {GRASS, MOUNTAINS, FOREST, SWAMP};

class Landscape{
protected:
    explicit Landscape() = default;
public:
    virtual char getName() = 0;
    virtual void changeAttribute(Unit *unit) = 0;
    virtual Land getLandName() = 0;
};
#endif //OOP_LANDSCAPE_H
