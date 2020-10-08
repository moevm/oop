#include "../Headers/UnitFactory.h"

Unit *Tier1Factory::createType1() {
    return new Knight;
}

Unit *Tier1Factory::createType2() {
    return new Shieldman;
}

Unit *Tier2Factory::createType1() {
    return new Archer;
}

Unit *Tier2Factory::createType2() {
    return new Ranger;
}

Unit *Tier3Factory::createType1() {
    return new Caster;
}

Unit *Tier3Factory::createType2() {
    return new Healer;
}
