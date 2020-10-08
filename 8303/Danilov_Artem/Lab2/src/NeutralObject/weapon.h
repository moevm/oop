//
// Created by kot on 10.05.2020.
//

#ifndef WEAPON_H
#define WEAPON_H
#include "neutralObj.h"

class Weapon
{
public:
    virtual ~Weapon() = default;
    virtual void use(Unit&) = 0;
};

class GetWeapon : public NeutralObj
{
private:
    Weapon* weapon;
public:
    GetWeapon(Weapon* weapon) : weapon(weapon) {}

    ~GetWeapon()
    {
        delete weapon;
    }

    void operator += (Unit& unit)
    {
        weapon->use(unit);
    }

    std::string characteristics() const {return "weapon";}

    std::string getType() const {return "neutral";}
};

class Excalibur : public Weapon
{
public:
    void use(Unit& unit)
    {
        unit.getCharacteristics()->setDamage(unit.getCharacteristics()->getDamage() + 100);
    }
};

class Sting : public Weapon   // from Frodo with love
{
public:
    void use (Unit& unit)
    {
        unit.getCharacteristics()->setDamage(unit.getCharacteristics()->getDamage() + 30);
    }
};

class PurpleJediSword : public Weapon   // surprise mathe**cker
{
public:
    void use (Unit& unit)
    {
        unit.getCharacteristics()->setDamage(unit.getCharacteristics()->getDamage() + 70);
    }
};




#endif //WEAPON_H
