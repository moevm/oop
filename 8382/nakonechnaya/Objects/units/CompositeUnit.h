#ifndef OOP_COMPOSITEUNIT_H
#define OOP_COMPOSITEUNIT_H
#include "Unit.h"
#include <vector>

class CompositeUnit : public Unit{
public:
    char getName() final {return 'C';};
    void printUnits();
    void deleteUnit(Unit *unit);
    void addUnit(Unit *unit) {units.push_back(unit);};
    Unit& operator+=(NeutralObject &object) final {};
    std::vector <Unit*> getUnits() {return units;};
private:
    std::vector <Unit*> units;
};
#endif //OOP_COMPOSITEUNIT_H
