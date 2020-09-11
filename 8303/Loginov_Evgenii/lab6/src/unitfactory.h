#ifndef UNITFACTORY_H
#define UNITFACTORY_H

#include "Unit/UnitCreater.h"

class UnitFactory
{
    TankCreater tankCreater;
    ArmoredCarCreater armoredCarCreater;
    RiflemanCreater riflemanCreater;
    MedicCreater medicCreater;
    SniperCreater sniperCreater;
    RocketLauncherCreater rocketLauncherCreater;

public:
    UnitFactory();
    Unit* createUnit(char name, int x, int y);
};

#endif // UNITFACTORY_H
