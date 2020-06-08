//
// Created by therealyou on 10.03.2020.
//

#ifndef LAB1_FACTORIES_H
#define LAB1_FACTORIES_H
#include "FactoryOfAlliance.h"
#include "FactoryOfMagicians.h"
#include "FactoryOfOrcs.h"
#include "../Exception.h"

class Fabric
{
public:
    Unit* createUnit(char unitClass, ProfileUnit values)
    {
        Unit* newUnit = nullptr;
        switch (unitClass)
        {
            case 'p':
                newUnit = FactoryOfAlliance().createPeon();
                break;
            case 's':
                newUnit = FactoryOfAlliance().createShooter();
                break;
            case 'e':
                newUnit = FactoryOfMagicians().createElf();
                break;
            case 'w':
                newUnit = FactoryOfMagicians().createWitch();
                break;
            case 'g':
                newUnit = FactoryOfOrcs().createGoblin();
                break;
            case 't':
                newUnit = FactoryOfOrcs().createTroll();
                break;
            default:
                throw LogicException("non-exist unit class", std::to_string(unitClass));
        }
        newUnit->profileUnit = values;
        return newUnit;
    }
};

#endif //LAB1_FACTORIES_H
