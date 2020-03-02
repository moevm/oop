#ifndef NUKER_H
#define NUKER_H

#include "Units/combat.h"


class NukerWeapon;

class Nuker : public Combat // excuse me for confusing defenition :c
{
protected:
    void setWeapon(NukerWeapon *weapon);

    void changeHealth(float iHealth);
    void changeSteps(float iSteps);

    int getAttackRadius() const;
    float getBaseDamage() const;

private:
    const float iMaxHealth;
    float iHealth;

    const float iMaxSteps;
    float iSteps;

    const float iBaseDamage;
    const int iAttackRadius;

public:
    Nuker(Cell *cell,
          NukerWeapon *weapon,
          int iHealth,
          int iMaxSteps,
          int iBaseDamage,
          int iAttackRadius);

    float health() const override;
    float maxHealth() const override;
    float steps() const override;
    float maxSteps() const override;
    void updateSteps() override;
};



class Berserker : public Nuker
{
public:
    Berserker(Cell *cell, NukerWeapon *weapon);
    void draw(sf::RenderTarget *target, int rect_size) override;
    void move(Cell *dest) override;
    void attack(Unit* enemy) override;
    void damage(float dmg) override;
    void heal(float iAddHealth) override;
    void foothold(bool bMode) override;
    Object* copy(CellGrid *field) const override;
};

#endif // NUKER_H
