#ifndef OOP_GRASS_H
#define OOP_GRASS_H
#include "Landscape.h"

class Grass : public Landscape{
public:
    Grass() : Landscape() {landName = GRASS;};
    char getName() final {return 'G';};
    void changeAttribute(Unit *unit) final {
        if (unit->getUnitName() == ARCHER || unit->getUnitName() == LICH)
            unit->changeAttributes(30, -10, 0);
        else
            unit->changeAttributes(0, -10, 0);
    };
    Land getLandName() final {return landName;};
private:
    Land landName;
};
#endif //OOP_GRASS_H
