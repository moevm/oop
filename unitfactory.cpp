#include "unitfactory.h"

UnitFactory::UnitFactory()
{

}

Unit* UnitFactory::createUnit(char name, int x, int y)
{
    switch(name) {
    case 'C' : return armoredCarCreater.create(x, y); break;
    case 'T' : return tankCreater.create(x,y); break;
    case 'M' : return medicCreater.create(x,y); break;
    case 'R' : return riflemanCreater.create(x,y); break;
    case 'L' : return rocketLauncherCreater.create(x,y); break;
    case 'S': return sniperCreater.create(x,y); break;
    }
}
