//
// Created by Alex on 21.03.2020.
//

#include "UnitFactories.h"

UnitFactory::UnitFactory() {
    axe = new Axe();
    spear = new Spear();
    sword = new Sword();
    bow = new Bow();
    rod = new Rod();
    attackUnitArmor = new AttackUnitArmor();
    heavyUnitArmor = new HeavyUnitArmor();
    rangeUnitArmor = new RangeUnitArmor();
}

UnitFactory::~UnitFactory() {
    delete axe;
    delete spear;
    delete sword;
    delete bow;
    delete rod;
    delete attackUnitArmor;
    delete heavyUnitArmor;
    delete rangeUnitArmor;
}

Swordmen *UnitFactory::getSwordsmen(int x, int y) {
    return new Swordmen(x, y, sword, attackUnitArmor);
}

Spearmen *UnitFactory::getSpearmen(int x, int y) {
    return new Spearmen(x, y, spear, attackUnitArmor);
}

Knight *UnitFactory::getKnight(int x, int y) {
    return new Knight(x, y, sword, heavyUnitArmor);
}

King *UnitFactory::getKing(int x, int y) {
    return new King(x, y, sword, heavyUnitArmor);
}

Archer *UnitFactory::getArcher(int x, int y) {
    return new Archer(x, y, bow, rangeUnitArmor);
}

Magician *UnitFactory::getMagician(int x, int y) {
    return new Magician(x, y, rod, rangeUnitArmor);
}
