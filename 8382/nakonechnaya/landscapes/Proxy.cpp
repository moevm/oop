#include "Proxy.h"

Proxy::Proxy(Land land){
    switch (land){
        case GRASS:
            landscape = new Grass();
            break;
        case FOREST:
            landscape = new Forest();
            break;
        case MOUNTAINS:
            landscape = new Mountains();
            break;
        case SWAMP:
            landscape = new Swamp();
            break;
    }
}

void Proxy::changeAttribute(Unit *unit) {
    if (unit->getUnitName() == ARCHER || unit->getUnitName() == LICH || unit->getUnitName() == GRIFFIN)
        landscape->changeAttribute(unit);
}