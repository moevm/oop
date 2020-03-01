#ifndef UNIT_H
#define UNIT_H
#include <string>
#include <attributes.h>
#include "subject.h"

class Unit : public Subject
{
public:
    Unit();
    void deapth();
    Attributes *attributes;
    std::string armyType;

};

#endif // UNIT_H
