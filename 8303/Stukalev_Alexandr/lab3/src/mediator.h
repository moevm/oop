#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "field.h"

class Mediator
{
    Field* field;

public:
    Mediator(Field* field);
    void attack(Unit* unit, int x, int y);
};

#endif // MEDIATOR_H
