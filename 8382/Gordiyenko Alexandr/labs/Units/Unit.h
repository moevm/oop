#ifndef LABS_UNIT_H
#define LABS_UNIT_H

#include <iostream>
#include "../extra2/SubjectObserver.h"

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
        Params() { mana = 0; }
        int health;
        int armor;
        int damage;
        int mana;
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
    }
    void set_base_id(int id) { base_id = id; }
};

#endif //LABS_UNIT_H
