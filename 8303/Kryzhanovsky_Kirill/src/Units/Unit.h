//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_UNIT_H
#define LAB1_UNIT_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>
#include "../ProfileUnit.h"
#include "../SubjectObserve.h"
#include "../Landscapes/Landscape.h"
#include "UnitsType.h"
#include "../Landscapes/LandscapeProxy.h"

#define SCATTER 0.0 // разброс [0, 1) | элемент случайности


class Landscape;

class Unit : public SubjectObserve {
protected:
    // coords
    int x;
    int y;

    bool canAdded = true;

    double deltaAttribute(double attribute);

    double minAttribute(double attribute);

public:
    ProfileUnit profileUnit;

    void setSpeed(int speed);

    void setHealth(int health);

    void setArmor(int armor);

    void setDamage(int damage);

    void setRange(int rangeAttack);

    LandscapeProxy *landscape;

    UnitsType type;

    Unit(int speed, int armor, int damage, int health, int rangeAttack);

    void setId(int id);

    int getId() const;

    void setX(int x);

    void setY(int y);

    void addUnit();

    void deleteUnit();

    virtual char getCharType() const = 0;

    bool isCanAdded() const;

    int getRange() const;

    double getSpeed() const;

    double getHealth() const;

    double getArmor() const;

    double getDamage() const;

    void getDamage(int damage);

    int getX() const;

    int getY() const;

    void print() const;

    void attack(Unit &other);

    void attack(Unit *other);

    void death();

    friend std::ostream &operator<<(std::ostream &out, const Unit &);

    std::string getInfo();
};


#endif //LAB1_UNIT_H
