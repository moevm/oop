#ifndef ARMOR_H
#define ARMOR_H
#include "neutralobject.h"

class Armor
{
public:
    virtual void use(Unit*) = 0;
};

class ArcherArmor : public Armor
{
    void use(Unit* unit) override
    {
       unit->attributes->armor += 80;
    }
};

class CavalryArmor : public Armor
{
    void use(Unit* unit) override
    {
        unit->attributes->armor += 20;
    }
};

class InfantryArmor : public Armor
{
    void use(Unit* unit) override
    {
        unit->attributes->armor += 10;
    }
};

class GetArmor : public NeutralObject
{
private:
    Armor* armor;

public:
    GetArmor(){}
    GetArmor(Armor* a) : armor(a) {}
    void operator== (Unit* unit){
        armor->use(unit);
    }
};

#endif // ARMOR_H
