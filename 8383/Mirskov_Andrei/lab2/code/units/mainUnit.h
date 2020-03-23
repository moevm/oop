//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_MAINUNIT_H
#define OOP_LAB1_MAINUNIT_H


#include "unit.h"

class MainUnit: public Unit {
public:
    int getHealth() override;

    void heal(int health) override;

    bool takeDamage(int damage) override;

    void setDamage(int) override;

    void setArmor(int) override;

    int getArmor() override;

    int getDamage() override;

    int getX() override;

    void setX(int newX) override;

    int getY() override;

    void setY(int newY) override;

    void takeItem(Potion*) override;

    void takeItem(Weapon*) override;

    void takeItem(Clothes*) override;

    void takeItem(Kit*) override;

    void operator += (Neutral*) override;


protected:
    int x, y;
    Armor armor;
    Damage damage;
    Health health;
    int maxHealth;
};


#endif //OOP_LAB1_MAINUNIT_H
