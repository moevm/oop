#ifndef UNIT_H
#define UNIT_H
#include <string>
#include "Object.h"

class Unit : public Object
{
protected:
    explicit Unit(std::string = "");
    std::string type() const override;
};

#endif // UNIT_H
