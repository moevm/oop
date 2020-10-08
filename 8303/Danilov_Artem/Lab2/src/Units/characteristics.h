//
// Created by kot on 28.02.2020.
//

#ifndef CHARACTERISTICS_H
#define CHARACTERISTICS_H


class Characteristics
{
private:
    int health;
    int damage;
    int armor;   // 2
    int stepLimits;

public:
    Characteristics();

    void setAll(int health, int damage, int armor, int stepLimits=2);

    int getHealth() const;
    void setHealth(int value);

    int getDamage() const;
    void setDamage(int value);

    int getArmor() const;
    void setArmor(int value);

    int getStepLimits() const;
    void setStepLimits(int value);
};


#endif //CHARACTERISTICS_H
