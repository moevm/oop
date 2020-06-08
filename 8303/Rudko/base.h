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
    int base_x, base_y;
    bool flag_base = 0;

public:
    int counter = 0;
    Base(int, int, GField*);
    void CreatureUnit(int, int, std::string);
    int getCount();
    int getHealth();
    void Condition();
    int Control(int, int, std::string, int);
};

#endif // BASE_H
