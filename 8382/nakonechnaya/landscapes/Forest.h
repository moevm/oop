#ifndef OOP_FOREST_H
#define OOP_FOREST_H
#include "Landscape.h"

class Forest : public Landscape{
public:
    Forest() : Landscape() {landName = FOREST;};
    char getName() final {return 'F';};
    void changeAttribute(Unit *unit) final {unit->changeAttributes(-10, 0, 0);};
    Land getLandName() final {return landName;};
private:
    Land landName;
};
#endif //OOP_FOREST_H
