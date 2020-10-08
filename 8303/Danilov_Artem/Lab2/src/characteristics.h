//
// Created by kot on 28.02.2020.
//

#ifndef CHARACTERISTICS_H
#define CHARACTERISTICS_H


class Characteristics {
public:
    Characteristics();

    void setAll(int strength, int agility, int intelligence,
            int health, int damage, int armor, int stepLimits);

    void setAll(int strength, int agility, int intelligence);

    int getStrength() const;
    void setStrength(int value);

    int getAgility() const;
    void setAgility(int value);

    int getIntelligence() const;
    void setIntelligence(int value);

    int getHealth() const;
    void setHealth(int value);

    int getDamage() const;
    void setDamage(int value);

    int getArmor() const;
    void setArmor(int value);

    int getStepLimits() const;
    void setStepLimits(int value);


private:
    int strength;
    int agility;
    int intelligence;
    int health;
    int damage;
    int armor;   // 2
    int stepLimits;

};


#endif //CHARACTERISTICS_H
