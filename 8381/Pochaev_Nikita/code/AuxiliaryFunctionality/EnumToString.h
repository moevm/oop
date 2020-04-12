#ifndef OOP_ENUMTOSTRING_H
#define OOP_ENUMTOSTRING_H

#include <string>

#include "InformationHeaders/unitPar.h"

class EnumTostring
{
public:
    static std::string enumToString(eUnitsType type)
    {
        switch (type)
        {
            case CANNON_FODDER:
                return "Cannon fodder";
            case INFANTRY:
                return "Infantry";
            case SHOOTER:
                return "Shooter";
            case WIZARD:
                return "Wizard";
            case CAVALRY:
                return "Cavalry";
            case VALUES_FIRST:
                return "VALUES_FIRST";
            case COMPOSITE_UNIT:
                return "Composite unit";
            case VALUES_END:
                return "VALUES_END";
            case NONE_UNIT:
                return "Null unit";
        }
        return "Null unit";
    }
};

#endif //OOP_ENUMTOSTRING_H
