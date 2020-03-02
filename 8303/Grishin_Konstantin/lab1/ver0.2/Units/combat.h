#ifndef COMBAT_H
#define COMBAT_H

#include "Units/unit.h"


class Weapon;
class Cell;

class Combat : public Unit
{
    friend class AbstractCombatFactory;

public:
    enum Type{
        Melee,
        Range,
        Nuker
    };

protected:
    void setWeapon(Weapon *weapon);
    const Weapon* getWeapon() const;

    void setMode(bool bMode);
    bool getMode() const;

private:
    Team team;
    const Type combType;
    bool bMode;
    Weapon *weapon = nullptr;

public:
    ~Combat();
    Combat(Cell *cell, Combat::Type combType);
    Combat::Type getCombatType() const;

    virtual void draw(sf::RenderTarget *target, int rect_size) = 0;
    virtual void move(Cell *dest) = 0;    // move with animation;

    virtual void damage(float dmg) = 0;   // probably should cast shell
                                        // instead int to differently
                                        // modificate damage

    virtual void heal(float iAddHealth) = 0;

    virtual float health() const = 0;
    virtual float maxHealth() const = 0;
    virtual float steps() const = 0;
    virtual float maxSteps() const = 0;
    virtual void updateSteps() = 0;

    virtual void attack(Unit* enemy) = 0;   // Probably should cast Cell, to modify damage
    virtual void foothold(bool bMode) = 0;
};


#endif // COMBAT_H
