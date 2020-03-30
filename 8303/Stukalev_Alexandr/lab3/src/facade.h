#ifndef FACADE_H
#define FACADE_H
#include "field.h"
#include "command.h"
class Facade
{
    Field* field;
public:
    Facade();
    void start();
};

#endif // FACADE_H
