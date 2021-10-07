#ifndef UNIT_H
#define UNIT_H

#include <QDebug>

struct Attributes {
    int health;
    int damage;
    int armor;
    int speed;
    char typeOfAttack; // s - shooting, m - melee
};

class Unit
{
    friend class GameField;
    int x;
    int y;
    bool isPosted = false;
protected:
    Attributes* mainAttributes;// = new Attributes;
    void setHealth(int value);
    void setDamage(int value);
    void setArmor(int value);
    void setSpeed(int value);
    void setTypeOfAttack(const int value);
public:

    int getHealth() const;
    int getDamage() const;
    int getArmor() const;
    int getSpeed() const;
    int getTypeOfAttack() const;

    Unit(int health, int damage, int armor, int speed);
    virtual char getID() const = 0;
    virtual ~Unit() {}
};

#endif // UNIT_H
