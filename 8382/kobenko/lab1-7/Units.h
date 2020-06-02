//
// Created by vlad on 01.06.2020.
//

#ifndef UNTITLED_UNITS_H
#define UNTITLED_UNITS_H

class Units {
public:
    int x;
    int y;
    char type;
    int health;
public:
    Units() = default;
    virtual int MoveUnits(int , int ) =0;
    virtual int AttackUnits() = 0;
    virtual void getDamage(int) =0;
private:
    int attack;
    int armor;
};


#endif //UNTITLED_UNITS_H
