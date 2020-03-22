#ifndef BASE_H
#define BASE_H

#include "field.h"

class Base;

class CreateMediator : public ICreateMediator
{
public:
    CreateMediator(Field *field, Base *base);
    void Notify(FieldItem *sender, FieldItem *unit, unsigned x, unsigned y);
private:
    Field *field;
    Base *base;
};


class Base : public IBase, public IBaseObserver
{
public:
    Base(unsigned unitLimit, unsigned number, std::string name, Field *field);

    bool isMovable() {
        return movable;
    }

    ~Base();

    std::string about();
    std::string shortName();
    unsigned getNumber();

    FieldItem *itemCopy();

    int getType(){
        return BASE;
    }

    void unitInfluence(IUnit *unit) {unit->getType();}
    void setMoveMediator(MoveMediator *value);

    IUnit* createUnit(unsigned x, unsigned y, UnitType type);

    std::list<Unit *> getUnitTypeList(UnitType type);

    std::list<Unit *> getUnitList();

    void setCreateMediator(ICreateMediator *value);
    void setGameMediator(IGameMediator *value);

    void deleteUpdate(Unit *unit);

    void reduceStability(unsigned value);

    unsigned getStability() const;
    unsigned getUnitLimit() const;
    unsigned getUnitCounter() const;

private:
    unsigned unitLimit;
    unsigned unitCounter;
    unsigned stability;
    bool movable = false;

    unsigned number;
    std::string name;

    void sendUnitToField(FieldItem *item, unsigned x, unsigned y);

    DeviceFactory *attackFactory;
    DeviceFactory *supportFactory;
    DeviceFactory *simpleFactory;

    ComponentKeeper *units;

    ICreateMediator *createMediator;
    IGameMediator *gameMediator;
    MoveMediator *moveMediator;
};

#endif // BASE_H
