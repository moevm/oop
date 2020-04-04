#include "UnitFactory.h"
#include "Melee.h"
#include "Ranged.h"
#include "SiegeEngine.h"


Unit* UnitFactory::produce(uint8_t unitType, Point point, Base* base) {
    Unit* unit;
    switch(unitType) {
    case UNIT_SWORDSMAN:
        unit = new Swordsman(point, base);
        break;
    case UNIT_PIKEMAN:
        unit = new Pikeman(point, base);
        break;
    case UNIT_SHOCK_CAVALRY:
        unit = new ShockCavalry(point, base);
        break;
    case UNIT_ARCHER:
        unit = new Archer(point, base);
        break;
    case UNIT_CROSSBOWMAN:
        unit = new Crossbowman(point, base);
        break;
    case UNIT_SCOUT_CAVALRY:
        unit = new ScoutCavalry(point, base);
        break;
    case UNIT_CATAPULT:
        unit = new Catapult(point, base);
        break;
    case UNIT_RAM:
        unit = new Ram(point, base);
        break;
    }
    return unit;
}
