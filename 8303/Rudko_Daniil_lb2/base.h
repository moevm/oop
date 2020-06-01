#ifndef BASE_H
#define BASE_H

#include "unit.h"
#include "gfield.h"
#include <string>

class Base
{
private:
    GField* field;
    int base_helth;
    int counter = 0;
    bool flag_base = 0;

public:
    Base(int, int, GField*);
    void CreatureUnit(int, int, std::string);
    int getCount();
};

#endif // BASE_H
