//
// Created by anton on 11.03.2020.
//

#ifndef OOP_1_BASE_H
#define OOP_1_BASE_H

#include <vector>

#include "Units/Unit.h"
#include "Units/Bard.h"
#include "Units/Dwarf.h"
#include "Units/Elf.h"
#include "Units/Flamen.h"
#include "Units/Necromancer.h"
#include "Units/Paladin.h"
#include "Field.h"
#include "Observer.h"

class Unit;
class Field;

class Base : public Observer{
    std::vector<Unit*> unitsList;
    int health;
    int currentUnitNumber;
    const int maxNumberUnits;
    const int x,y;
    Field* field;
public:
    Base(Field*, int, int, int);

    void createUnit(char);

    void deleteUnit(Unit*);

    void update(Subject*) override ;
};


#endif //OOP_1_BASE_H
