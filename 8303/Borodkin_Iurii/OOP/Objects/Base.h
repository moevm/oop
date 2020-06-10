#ifndef BASE_H
#define BASE_H
#include "Object.h"
#include "Units/Units.h"
#include "Linker/Linker.h"
#include <queue>
#include <list>

class Base : public Object
{
    const unsigned maxNumUnits;
    HeapUnit barrack;

public:
    Base(string = "", unsigned = 0, unsigned = 0);

    bool createUnit(Unit*) override;

    bool empty() const override;

    Unit* getUnit() override;

    string type() const override;

    unsigned travelDistance() const override;

    void attack() override;

    void getDamage(unsigned) override;

    void heal(unsigned int) override;

    const HeapUnit &getHeap() const;

    ~Base() override;
};

#endif // BASE_H
