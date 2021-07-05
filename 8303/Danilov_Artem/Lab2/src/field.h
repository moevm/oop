//
// Created by kot on 25.02.2020.
//

#ifndef FIELD_H
#define FIELD_H

#include "libraries.h"
#include "land.h"

class Field;
class MoveMediator;

class FieldItem{

public:
    virtual ~FieldItem() = default;
    virtual bool isMovable() = 0;
    virtual std::string about() = 0;
    virtual std::string shortName() = 0;
    virtual FieldItem* itemCopy() = 0;
    virtual void move(int x, int y) = 0;
    virtual void setMoveMediator(MoveMediator *value) = 0;
};

class Field{
public:
    Field(unsigned width, unsigned height, unsigned itemLimit);
    Field(const Field &field);
    Field(Field &&field);

    unsigned getWidth() const;
    unsigned getHeight() const;
    unsigned getItemCounter() const;
    bool addItem(unsigned x, unsigned y, FieldItem *item);
    bool deleteItem(unsigned x, unsigned y);
    bool deleteItem(FieldItem *item);
    bool moveItem(FieldItem *item, int x, int y);
    std::string getAbout(unsigned x, unsigned y);
    std::string getShortInfo();
    void setItemLimit(const unsigned &value);
    void setMoveMediator(MoveMediator *value);
    FieldItem *getItem(unsigned x, unsigned y) const;
    Field &operator=(const Field &field);
    Field &operator=(Field &&field);

    void addLand(unsigned x, unsigned y, Proxy *landscape);

    ~Field();

private:
    const unsigned width;
    const unsigned height;
    const unsigned itemLimit;
    unsigned itemCounter;
    FieldItem ***items;
    Proxy*** land;
    MoveMediator *moveMediator;

};


class FieldIterator
{
public:
    FieldIterator( const Field *field);
    bool isActive() const;
    FieldItem *operator->() const;
    FieldItem *operator++();

private:
    bool active;
    const Field *field;
    unsigned curWidth;
    unsigned curHeight;
};

class MoveMediator{
public:
    MoveMediator(Field *field, FieldItem *item);
    void notify(FieldItem *sender, int x, int y);
private:
    Field *field;
    FieldItem *item;
};

#endif //FIELD_H
