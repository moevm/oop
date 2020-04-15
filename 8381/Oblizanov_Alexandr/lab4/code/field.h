#ifndef FIELD_H
#define FIELD_H

#include "component.h"

class FieldIterator
{
public:
    FieldIterator(Field *field);
    bool isActive();
    FieldItem *operator->();
    FieldItem *operator++();

    unsigned getCurWidth() const;
    unsigned getCurHeight() const;

private:
    bool active;
    Field *field;
    unsigned curWidth;
    unsigned curHeight;
};

class Field
{
public:
    Field(unsigned width, unsigned height, unsigned itemLimit, LandType basicLand);
    Field(const Field &field);
    Field(Field &&field);

    ~Field();

    unsigned getWidth() const;

    unsigned getHeight() const;

    unsigned getItemLimit() const;
    void setItemLimit(const unsigned &value);

    unsigned getItemCounter() const;

    std::string getAbout(unsigned x, unsigned y);

    LandType getLandType(unsigned x, unsigned y);

    std::string getShortInfo();

    bool addItem(unsigned x, unsigned y, FieldItem *item);

    bool addLandscape(unsigned x, unsigned y, FieldLandscape *landscape);

    bool addBaseUnit(unsigned x, unsigned y, FieldItem *base, FieldItem *unit);

    bool deleteItem(unsigned x, unsigned y);

    bool deleteItem(FieldItem *item);

    FieldItem *getItem(unsigned x, unsigned y);

    bool moveItem(IUnit *item, int x, int y);

    void setMoveMediator(MoveMediator *value);

    void setCreateMediator(ICreateMediator *value);

    Field &operator=(const Field &field);
    Field &operator=(Field &&field);

private:
    unsigned width;
    unsigned height;
    FieldItem ***items;
    FieldLandscape ***landscapes;
    unsigned itemLimit;
    unsigned itemCounter;
    MoveMediator *moveMediator;
    ICreateMediator *createMediator;

};

#endif // FIELD_H
