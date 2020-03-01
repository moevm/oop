#ifndef MEDICINE_H
#define MEDICINE_H
#include "neutralobject.h"

class Medicine
{
public:
    virtual void use(Unit*) = 0;
};

class ArcherMedicine : public Medicine
{
    void use(Unit* unit) override
    {
        unit->attributes->health += 5;
    }
};

class CavalryMedicine : public Medicine
{
    void use(Unit* unit) override
    {
        unit->attributes->health += 15;
    }
};

class InfantryMedicine : public Medicine
{
    void use(Unit* unit) override
    {
        unit->attributes->health += 10;
    }
};

class GetMedicine : public NeutralObject
{
private:
    Medicine* medicine;

public:
    GetMedicine(){}
    GetMedicine(Medicine* m) : medicine(m) {}
    void operator== (Unit* unit){
        medicine->use(unit);
    }
};

#endif // MEDICINE_H
