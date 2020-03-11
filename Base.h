//
// Created by Evgeniy on 3/8/2020.
//

#ifndef OOP1_3_BASE_H
#define OOP1_3_BASE_H

#include <vector>

#include "Field.h"
#include "unitfactory.h"

class Base {
    friend class Field;
private:
    Field *field;
    int x, y;
    UnitFactory unitFactory;
    std::vector<Unit*> unitsAtBase;
    int maxCountUnit, health, countUnit;
public:
    Base(Field* field, int x, int y, int maxCountUnit, int health);
    void createUnit(char name);
    void printUnits() const;
};


#endif //OOP1_3_BASE_H
