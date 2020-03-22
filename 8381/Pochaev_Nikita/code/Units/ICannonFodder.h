#ifndef OOP_ICANNONFODDER_H
#define OOP_ICANNONFODDER_H

#include "Unit.h"

class ICannonFodder
{
protected:
    virtual void train() = 0;
    virtual bool cowardice() = 0;

    virtual ~ICannonFodder() = default;
};

#endif //OOP_ICANNONFODDER_H