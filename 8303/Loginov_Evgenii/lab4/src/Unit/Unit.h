//
// Created by Jack on 08/03/2020.
//

#ifndef OOP1_3_UNIT_H
#define OOP1_3_UNIT_H

#include <iostream>
//#include "../Landscape/Landscape.h"

#include "../SubjectObserve.h"

class NeutralObject;

// Абстрактный класс Юнита
class Unit : public SubjectObserve {
    friend class NeutralObject;
    friend class Field;

    friend std::ostream& operator<< (std::ostream &out, Unit& unit);
public:
    class Params {
    public:
        int health;
        int armor;
        int distance;
        int damage;
        int fuel;

       // Landscape* landscape;
    } param;

protected:
    int x, y;
public:
    void move(int x, int y){
        this->x = x;
        this->y = y;
    }
    int getx() { return x; }
    int gety() { return y; }
    void print() {
        std::cout << type();
    }
    virtual char type() = 0;

    void death() { this->notify(); }
};



#endif //OOP1_3_UNIT_H
