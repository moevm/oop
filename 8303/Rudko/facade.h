#ifndef FACADE_H
#define FACADE_H

#include "unit.h"
#include "gfield.h"
#include "base.h"
#include "memento.h"
#include "log.h"

#include <string>

class Facade
{
private:
    GField* field;
    Base* base;
    Memento* s;
    log* l;
    log* l1;

public:
    void NewGame(int, int);
    void Play(int);
};

#endif // FACADE_H
