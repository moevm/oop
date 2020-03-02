//
// Created by anton on 16.02.2020.
//

#ifndef OOP_1_UNIT_H
#define OOP_1_UNIT_H

#include "Cell.h"
#include "Field.h"

class Field;
class Cell;
class Unit {
    int health;
    int armor;
    int attack;
    int attackRange;
    Field* gameField;
    int x;
    int y;
public:
    Unit();
    bool isOnField();
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    void move(int X, int Y);
    void replace(Field* gameField);
    virtual char getClass() const = 0 ;
    void deleteFromField();

    friend class Wizard;
    friend class Warrior;
    friend class Thief;

    friend class Elf;
    friend class Bard;
    friend class Dwarf;
    friend class Paladin;
    friend class Flamen;
    friend class Necromancer;
    };


#endif //OOP_1_UNIT_H
