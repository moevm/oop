#ifndef DWARF_H
#define DWARF_H

#include "Unit/infantryunit.h"


class Dwarf : public InfantryUnit
{
public:
    //поменять
    Dwarf(Mediator* mediator);
    ~Dwarf();

    void regeneration() override;

    Unit* clone() override;
};

#endif // DWARF_H
