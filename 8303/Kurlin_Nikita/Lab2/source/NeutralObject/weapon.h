#ifndef WEAPON_H
#define WEAPON_H
#include "neutralobject.h"

class Weapon
{
public:
    virtual void use(Unit*) = 0;
};

class ArcherWeapon : public Weapon
{
    void use(Unit* unit) override
    {
        unit->attributes->attack += 25;
    }
};

class CavalryWeapon : public Weapon
{
    void use(Unit* unit) override
    {
        unit->attributes->attack += 5;
    }
};

class InfantryWeapon : public Weapon
{
    void use(Unit* unit) override
    {
        unit->attributes->attack += 10;
    }
};

class GetWeapon : public NeutralObject
{
private:
    Weapon* weapon;

public:
    GetWeapon(){}
    GetWeapon(Weapon* w) : weapon(w) {}
    void operator== (Unit* unit){
        weapon->use(unit);
    }
};
#endif // WEAPON_H
