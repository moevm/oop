#ifndef BATTLE_FOR_HONOR_ATTRIBUTES_H
#define BATTLE_FOR_HONOR_ATTRIBUTES_H


#include "Damage.h"
#include "Armour.h"

class Attributes{


private:
    int distance;
    int speed;
    char symbol;
    Armour* armour;
    Damage* damage;
public:
    Attributes(){
        distance = 0;
        speed = 0;
        symbol = 0;
        armour = new Armour();
        damage = new Damage();
    }
    //getters
    int getDistance();
    int getSpeed();
    char getSymbol();
    Armour* getArmour();
    Damage* getDamage();
    //setters
    void setDistance(int distance);
    void setSpeed(int speed);
    void setSymbol(char symbol);
    void setArmour(std::string armour);
    void setDamage(std::string damage);

};


#endif //BATTLE_FOR_HONOR_ATTRIBUTES_H
