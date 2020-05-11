#ifndef UNITPARAM_H
#define UNITPARAM_H
#include "attributes.h"
#include <iostream>
using namespace std;
class UnitParam
{
public:
    UnitParam(string name, int baseNumber,  Attributes* attributes);
    string getName() const;

    int getBaseNumber() const;

    Attributes *getAttributes() const;

private:
    string name;
    int baseNumber;
    Attributes* attributes;

};

#endif // UNITPARAM_H
