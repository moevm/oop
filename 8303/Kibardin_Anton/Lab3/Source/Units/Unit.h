//
// Created by anton on 16.02.2020.
//

#ifndef OOP_1_UNIT_H
#define OOP_1_UNIT_H

#include "../Observer.h"
#include <string>
#include <iostream>
class Specifications
{
public:
    int health;
    int armor;
    int attack;
    int attackRange;
};

class Unit: public Subject {
    int x, y;
    std::string unitName;
public:
    void setName(std::string&);

    void setX(int);

    void setY(int);

    int getX() const;

    int getY() const;

    std::string getName() const;

    Specifications values;

    Unit();

    Unit(Specifications values);

    virtual char getClass() const = 0 ;

    void death();

    void printSpecifications() const;

    void getDamage(int);

    friend  std::ostream& operator<<(std::ostream& out, const Unit&);

};


#endif //OOP_1_UNIT_H
