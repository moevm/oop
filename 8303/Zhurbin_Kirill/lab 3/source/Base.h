#ifndef OOP1_BASE_H
#define OOP1_BASE_H


#include <vector>
#include "Unit.h"
#include "CompositUnit.h"

class Field;

class Base: public Observer {
    friend class Field;
    friend class StatusBaseCommand;
private:
    int BaseX, BaseY;
    Field* field;
    int current;
    CompositUnit* compositUnit;
    int maxCountUnit, health, countUnit;
    Base(Field* fileldint, int maxCountUnit, int health, int BaseX, int BaseY);
public:
    void update(SubjectObserve* subject);
    void removeUnit(Unit* unit);
    void printUnit();

    bool createUnit(char name, Mediator* mediator);

    int getCapacityUnit();

    Unit *getUnit();

    bool wasAttack(int damage);
};


#endif //OOP1_BASE_H
