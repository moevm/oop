//
// Created by anton on 11.03.2020.
//

#ifndef OOP_1_BASE_H
#define OOP_1_BASE_H

#include <vector>
#include <iostream>

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
    const int baseNumber;
    std::vector<Unit*> unitsList;
    int health;
    int currentUnitNumber;
    const int maxNumberUnits;
    const int x,y;
    Field* field;
    int savingCounter;
public:
    Base(Field*, int, int, int, int, int);

    void createUnit(char, std::string);

    void createUnit(char, std::string, int, int, Specifications);

    void deleteUnit(Unit*);

    void update(Subject*) override ;

    void getDamage(int);

    int getNumber() const;

    void printStatus() const;

    Unit* findUnit(std::string unitName);

    friend  std::ostream& operator<<(std::ostream& out, const Base&);

    std::string getUnitsInfo();
    std::string getBaseInfo() const;
};


#endif //OOP_1_BASE_H