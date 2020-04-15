#pragma once

#include <fstream>
#include "Cell.h"


class Field
{
    friend class GameFacade;

public:
    Field(uint16_t width, uint16_t height, uint8_t landscapeType);
    Field(std::ifstream& stream);
    ~Field();

    Field(const Field& field);
    Field& operator=(Field& field);
    Field(Field&& field);
    Field& operator=(Field&& field);

    uint16_t getWidth();
    uint16_t getHeight();


    ILandscape* getLandscape(Point point);

    void setUnit(Point point, IUnit* unit);
    IUnit* getUnit(Point point);
    void removeUnit(Point point);

    void setBase(Point point, Base* base);
    Base* getBase(Point point);
    void removeBase(Point point);

    void setContext(Point point, NeutralContext* context);
    NeutralContext* getContext(Point point);

    bool isUnitFree(Point point);
    bool isBuildingFree(Point point);
    uint8_t getBuildingGroupType(Point point);


    bool isBelowMaxUnitCount();


    class Iterator;
    friend class Iterator;

    Iterator begin();
    Iterator end();

private:
    Cell* getCell(Point point);


    uint16_t width;
    uint16_t height;
    Cell** cellArray;

    uint16_t unitCount;
    uint16_t maxUnitCoint;
};


class Field::Iterator
{
public:
    Iterator(Field* field, Cell* cell);

    Cell& operator*();
    Cell* operator->();

    friend bool operator== (const Field::Iterator& iter1, const Field::Iterator& iter2);
    friend bool operator!= (const Field::Iterator& iter1, const Field::Iterator& iter2);

    Cell& operator++();
    Cell& operator++(int);
    Cell& operator--();
    Cell& operator--(int);

    Cell& operator+=(int n);
    Cell& operator-=(int n);

    Cell& operator+(int n);
    Cell& operator-(int n);

private:
    Field* field;
    Cell* cell;
};
