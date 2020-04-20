//
// Created by Jack on 08/03/2020.
//

#ifndef OOP1_3_FIELD_H
#define OOP1_3_FIELD_H

#include "Unit/Unit.h"
#include "Landscape/Landscape.h"
#include <iostream>
#include "adapter.h"

struct Cell{
    int x, y;
    Unit* unit;
    Landscape* landscape;
    NeutralObject* object;

    Cell(int x,int y, Unit* unit, Landscape* landscape, NeutralObject* object) : 
        x(x), y(y), 
        unit(unit), 
        landscape(landscape),
        object(object)
    {}
};

class Base;

class Field {
    friend std::ostream& operator<< (std::ostream &out, const Field& field);
   const int x, y;
    const int maxUnit;
    int curUnit;
    Base *base;
    Cell ***cell; //матрица(двумерный) указателей на юниты. в каждой ячейке матрцы адрес юнита

public:
    Adapter* adapter;

    friend class Iterator;
    Field(int x, int y, int maxUnit, Adapter* adapter);

    //копирование поля. сслыка на другое поле,
    Field(const Field &field);
    Field(Field &&field);
    void addUnit(Unit* unit);
    Base* createBase(int x, int y, int maxCountUnit, int health);

    Base* getBase() { return base; }

    void removeUnit(Unit* unit);
    void print();

    bool moveUnit(Unit* unit, int x, int y);

    void addLandscape();

    void printLandscape();
};

#endif //OOP1_3_FIELD_H
