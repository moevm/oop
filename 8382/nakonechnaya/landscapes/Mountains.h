#ifndef OOP_MOUNTAINS_H
#define OOP_MOUNTAINS_H
#include "Landscape.h"

class Mountains : public Landscape{
public:
    Mountains() : Landscape() {landName = MOUNTAINS;};
    char getName() final {return 'M';};
    void changeAttribute(Unit *unit) final {unit->changeAttributes(10, 0, 0);};
    Land getLandName() final {return landName;};
private:
    Land landName;
};
#endif //OOP_MOUNTAINS_H
