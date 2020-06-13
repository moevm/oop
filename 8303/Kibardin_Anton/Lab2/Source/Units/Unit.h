//
// Created by anton on 16.02.2020.
//

#ifndef OOP_1_UNIT_H
#define OOP_1_UNIT_H

#include "../Observer.h"
#include <cstdio>

class Specifications
{
public:
    int health;
    int armor;
    int attack;
    int attackRange;
};

class Unit: public Subject {
public:
    Specifications values;

    Unit();

    Unit(Specifications values);

    virtual char getClass() const = 0 ;

    void death();

    void printSpecifications() const;

};


#endif //OOP_1_UNIT_H
