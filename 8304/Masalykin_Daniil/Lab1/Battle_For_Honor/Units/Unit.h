#ifndef BATTLE_FOR_HONOR_UNIT_H
#define BATTLE_FOR_HONOR_UNIT_H


#include "Attributes.h"

class Unit {
private:
    Attributes stats;
    int x;
    int y;
    int health;
public:
    int getX();
    int getY();
    Attributes getStats();
    int getHealth();
    int getDistance();
    int getSpeed();
    char getSymbol();
    Armour* getArmour();
    Damage* getDamage();
    Unit();
    void setStats(Attributes stats);
    void setHealth(int health);
    void setX(int x);
    void setY(int Y);
    void setDistance(int distance);
    void setSpeed(int speed);
    void setSymbol(char symbol);
    void setArmour(std::string armour);
    void setDamage(std::string damage);
};


#endif //BATTLE_FOR_HONOR_UNIT_H
