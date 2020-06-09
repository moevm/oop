//
// Created by Jack on 08/03/2020.
//

#ifndef OOP1_3_FIELD_H
#define OOP1_3_FIELD_H

#include "Unit/Unit.h"
#include "Landscape/Landscape.h"
#include <iostream>

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
//    Base* base;
//    NeutralObject* neutralObject;
};

class Base;

class Field {
   const int x, y;
    const int maxUnit;
    int curUnit;
    Base *base;
    Cell ***cell; //матрица(двумерный) указателей на юниты. в каждой ячейке матрцы адрес юнита

public:
    Field(int x, int y, int maxUnit);
    //копирование поля. сслыка на другое поле,
    Field(const Field &field);
    Field(Field &&field);
    void addUnit(Unit* unit);
    Base* createBase(int x, int y, int maxCountUnit, int health);

    void removeUnit(Unit* unit);
    void print();
    void printBaseInfo();

    void moveUnit(Unit* unit, int x, int y);


};

#endif //OOP1_3_FIELD_H
