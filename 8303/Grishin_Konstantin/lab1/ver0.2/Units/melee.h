#ifndef MELEE_H
#define MELEE_H

#include "Units/combat.h"


class MeleeWeapon;

class Melee : public Combat
{
protected:
    void setWeapon(MeleeWeapon *weapon);

    void changeHealth(float iHealth);
    void changeSteps(float iSteps);

    int getBaseDamage()const;

private:
    const float iMaxHealth;
    float iHealth;

    const float iMaxSteps;
    float iSteps;

    const int iBaseDamage;

public:
    Melee(Cell *cell,
          MeleeWeapon* weapon,
          int iMaxHealth,
          int iMaxSteps,
          int iBaseDamage);

    float health() const override;
    float maxHealth() const override;
    float steps() const override;
    float maxSteps() const override;
    void updateSteps() override;
};



class Barbarian : public Melee
{
private:
    // there should be animation frames vectors
    // and animation run functions;

public:
    Barbarian(Cell *cell, MeleeWeapon *weapon);
    void draw(sf::RenderTarget *target, int rect_size);
    void move(Cell *dest);
    void attack(Unit* enemy);
    void damage(float dmg);
    void foothold(bool bMode);
    void heal(float iAddHealth);
    Object* copy(CellGrid *field) const;
};

#endif // MELEE_H
