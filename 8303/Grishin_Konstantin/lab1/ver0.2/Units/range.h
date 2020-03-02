#ifndef RANGE_H
#define RANGE_H


#include "Units/combat.h"


class RangeWeapon;

class Range : public Combat
{
protected:
    void setWeapon(RangeWeapon *weapon);

    void changeHealth(float iHealth);
    void changeSteps(float iSteps);

    int getAttackRadius() const;

private:
    const float iMaxHealth;
    float iHealth;

    const int iMaxSteps;
    float iSteps;

    const int iAttackRaduis;

public:
    Range(Cell *cell,
          RangeWeapon *weapon,
          int iMaxHealth,
          int iMaxSteps,
          int iAttackRadius);

    float health() const override;
    float maxHealth() const override;
    float steps() const override;
    float maxSteps() const override;
    void updateSteps() override;
};



class Archer : public Range
{
public:
    Archer(Cell *cell, RangeWeapon *weapon);
    void draw(sf::RenderTarget *target, int rect_size) override;
    void move(Cell *dest) override;
    void attack(Unit *enemy) override;
    void damage(float dmg) override;
    void foothold(bool bMode) override;
    void heal(float iAddHealth) override;
    Object* copy(CellGrid *field) const override;
};

#endif // RANGE_H
