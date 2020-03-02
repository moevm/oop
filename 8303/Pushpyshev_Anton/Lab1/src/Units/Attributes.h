#ifndef BATTLE_FOR_HONOR_ATTRIBUTES_H
#define BATTLE_FOR_HONOR_ATTRIBUTES_H


#include "Damage.h"
#include "Armour.h"

class Attributes{


public:
    int health;
    int distance;
    int speed;
    int x;
    int y;
    char symbol;
    Armour* armour;
    Damage* damage;
    Attributes(){
        health = 0;
        distance = 0;
        speed = 0;
        x = 0;
        y = 0;
        symbol = 0;
        armour = new Armour();
        damage = new Damage();
    }

};


#endif //BATTLE_FOR_HONOR_ATTRIBUTES_H
