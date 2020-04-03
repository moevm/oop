//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_UNIT_H
#define OOP_LB1__2_UNIT_H


#include "../Armor/Armor.h"
#include "../Weapon/Weapon.h"
#include "../Map/Point.h"
#include <string>

class Unit {

    friend class Field;

protected:
    Armor armor;
    Weapon weapon;
    int health;

    Point coordinates;

protected:
    Unit(){}
    Point& getCoordinates() { return coordinates; }

public:
    virtual std::string type() const { return "Unit"; }
    virtual ~Unit() = default;


};


#endif //OOP_LB1__2_UNIT_H
