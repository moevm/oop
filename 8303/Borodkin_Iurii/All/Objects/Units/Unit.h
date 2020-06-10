#ifndef UNIT_H
#define UNIT_H
#include <string>
#include "Objects/Object.h"
#include "../Linker/Linker.h"

enum class Units
{
    ARCHER, PANZER,
    SPEARMAN, WIZARD,
    CENTAUR, SWORDSMAN
};

class Unit : public Object, public IUnit
{
protected:
    explicit Unit(string = "");

    void add(const UnitPtr &) override;

    void remove(const UnitPtr &) override;

public:
    string type() const override = 0;

    void attack() override;
};

#endif // UNIT_H
