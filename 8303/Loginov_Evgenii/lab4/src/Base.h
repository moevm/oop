//
// Created by Evgeniy on 3/8/2020.
//

#ifndef OOP1_3_BASE_H
#define OOP1_3_BASE_H

#include <vector>
#include "Field.h"
#include "unitfactory.h"
#include "unitsgroup.h"
#include "Observer.h"

class Base : public Observer{
    friend class Field;
    friend std::ostream& operator<< (std::ostream &out, Base& base);

private:
    Field *field;
    int x, y;
    UnitFactory unitFactory;
    UnitsGroup unitsAtBase;
    UnitsGroup units;

    int maxCountUnit, health, countUnit;

public:
    Base(Field *field, int x, int y, int maxCountUnit, int health);
    Unit *createUnit(char name);
    void printInfo();
    void printUnits();

    bool isUnitAtBase(Unit *unit);

    void exitBase(Unit *unit);
    void enterBase(Unit *unit);

    Unit* getUnitById(int id);
    int countAllUnits() { return units.unitsGroup.size(); }

    void update(SubjectObserve *subject);
    friend  std::ostream& operator<<(std::ostream& out, const Base&);
};


#endif //OOP1_3_BASE_H
