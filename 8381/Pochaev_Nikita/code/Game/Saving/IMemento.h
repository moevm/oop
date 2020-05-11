#ifndef IMEMENTO_H
#define IMEMENTO_H

#include "SaveStuctures.h"

class IMemento
{
public:
    virtual ~IMemento() = default;
    virtual GameParametersCaretaker loadFromFile() = 0;
};

#endif // IMEMENTO_H
