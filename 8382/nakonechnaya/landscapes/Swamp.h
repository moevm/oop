#ifndef OOP_SWAMP_H
#define OOP_SWAMP_H
#include "Landscape.h"

class Swamp : public Landscape{
public:
    Swamp() : Landscape() {landName = SWAMP;};
    char getName() final {return 'S';};
    void changeAttribute(Unit *unit) final {unit->changeAttributes(-20, 0, 0);};
    Land getLandName() final {return landName;};
private:
    Land landName;
};
#endif //OOP_SWAMP_H
