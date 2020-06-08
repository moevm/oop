#ifndef USABLE_H
#define USABLE_H

#include "game_elements/neutral_objects/object.h"

class Unit;

class Usable : public Object
{
public:
    virtual Object* operator>>(class Unit* target) = 0;
};

#endif // USABLE_H
