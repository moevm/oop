//
// Created by kot on 08.05.2020.
//

#ifndef RANGE_H
#define RANGE_H
#include "../unit.h"

class Range : public Unit
{
public:
    virtual Unit *itemCopy() = 0;
};

#endif //RANGE_H
