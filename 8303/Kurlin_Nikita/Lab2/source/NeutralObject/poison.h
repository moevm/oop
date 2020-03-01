#ifndef POISON_H
#define POISON_H
#include "neutralobject.h"

class Poison
{
public:
    virtual void use(Unit*) = 0;
};

class ArcherPoison : public Poison
{
    void use(Unit* unit) override
    {
        unit->deapth();
    }
};

class CavalryPoison : public Poison
{
    void use(Unit* unit) override
    {
        unit->attributes->health -= 20;
    }
};

class InfantryPoison : public Poison
{
    void use(Unit* unit) override
    {
        unit->attributes->health -= 25;
    }
};

class DrinkPoison : public NeutralObject
{
private:
    Poison* poison;

public:
    DrinkPoison(){}
    DrinkPoison(Poison* p) : poison(p) {}
    void operator== (Unit* unit){
        poison->use(unit);
    }
};

#endif // POISON_H
