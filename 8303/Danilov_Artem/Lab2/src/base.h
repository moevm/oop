#ifndef BASE_H
#define BASE_H

#include "unit.h"

class Base : public IObserver
{
public:
    Base(Field *field);
    Base(Field *field, unsigned itemLimit);
    ~Base(){
        delete  moveMediator;
    }
    virtual bool isMovable() {
       return movable;
    }
    unsigned getHealth() const;
    std::string shortName();
    void setMoveMediator(MoveMediator *value){};
    std::string about(){return "";};
    void move(int x, int y) {};
    bool addUnit(unsigned x, unsigned y, FieldItem *item);
    FieldItem *itemCopy(){
        return new Base(field);
    };
    unsigned getItemCounter() const {
        return itemCounter;
    }

    FieldItem* addOrk(unsigned x, unsigned y);
    FieldItem* addKnight(unsigned x, unsigned y);
    FieldItem* addDryad(unsigned x, unsigned y);
    FieldItem* addWitch(unsigned x, unsigned y);
    FieldItem* addDragon(unsigned x, unsigned y);
    FieldItem* addChimera(unsigned x, unsigned y);
    FieldItem* deleteUnit(FieldItem *obj);

    //bool isMine()
private:
    Field *field;
    std::string name;
    unsigned health;
    const unsigned itemLimit;
    unsigned itemCounter;
    const bool movable = false;
    MoveMediator *moveMediator = nullptr;
protected:
    MeleeFactory* meleeFactory;
    SupportFactory* supportFactory;
    RangeFactory* rangeFactory;
};

#endif // BASE_H
