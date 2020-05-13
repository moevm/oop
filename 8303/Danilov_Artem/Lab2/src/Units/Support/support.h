//
// Created by kot on 08.05.2020.
//

#ifndef SUPPORT_H
#define SUPPORT_H
#include "../unit.h"

class Support : public Unit
{
public:
    virtual Unit *itemCopy() = 0;
};
#endif //SUPPORT_H
