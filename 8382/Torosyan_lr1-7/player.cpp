#include <iostream>
#ifndef UNITS
#define UNITS
#include "units.cpp"
#endif
using std::string;
class Player
{
public:
    int money=0;
    std::string faction="";
    UnitHQ* hq=nullptr;
};
