#ifndef UNIT_H
#define UNIT_H
#include <string>
#include <iostream>
#include "attributes.h"
#include "subject.h"
#include "basecomponent.h"

class Unit : public Subject, public BaseComponent
{
public:
    Unit();
    void deapth();
    void getDamage(int);
    Attributes *attributes;
    std::string armyType;
    std::string name;

};

#endif // UNIT_H
