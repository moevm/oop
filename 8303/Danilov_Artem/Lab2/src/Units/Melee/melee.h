//
// Created by kot on 08.05.2020.
//

#ifndef MELEE_H
#define MELEE_H
#include "../unit.h"

class Melee : public Unit
{
public:
    virtual Unit *itemCopy() = 0;
};
#endif //MELEE_H
