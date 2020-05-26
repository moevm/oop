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
    friend class SnapshotBackup;
    friend std::ostream& operator<< (std::ostream &out, Unit& unit);
public:
    class Params {
    public:
        Params() { fuel = 0; }
        int health;
        int armor;
        int damage;
        int fuel;

       // Landscape* landscape;
    } param;

protected:
    int base_id;
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

    void death() {
        std::cout << "death of unit" << type() <<" from base #" << base_id << std::endl;
        this->notify();
    }

    void set_base_id(int id) { base_id = id; }
};



#endif //OOP1_3_UNIT_H
