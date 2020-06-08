//
// Created by therealyou on 09.03.2020.
//

#ifndef LAB1_BASE_H
#define LAB1_BASE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Units/Unit.h"
#include "Factories/Factories.h"
#include "Observer.h"
#include "GameField.h"

class GameField;

class Base : public Observer {
    GameField *gameField;
    int countUnits, maxCountUnits, health, savingCounter;
    std::vector<Unit *> units;
    const int x, y;

public:
    const int baseNumber;

    Base(GameField *gameField, int x, int y, int baseNumber, int maxCountUnits = 3, int health = 100);

    Unit *createUnit(UnitsType unit, int x, int y, int unitId);

    Unit *createUnit(char unit, int x, int y, ProfileUnit value);

    void print(bool full = false) const;

    const std::vector<Unit *> &getUnits() const;

    std::vector<Unit*> getUnits();

    void deleteUnit(Unit *unit);

    void update(SubjectObserve *subjectObserve);

    void getDamage(int damage);

    friend std::ostream &operator<<(std::ostream &out, const Base &);

    std::string getUnitsInfo();

    std::string getBaseInfo() const;

    Unit* findUnit(int unitId);
};


#endif //LAB1_BASE_H
