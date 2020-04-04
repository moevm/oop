#include "SiegeEngine.h"
#include "Game/Game.h"


/* SIEGE SIEGE SIEGE SIEGE SIEGE SIEGE SIEGE SIEGE SIEGE SIEGE */

SiegeEngine::SiegeEngine(Point point, Base* base) : Unit(point, base) {

}

uint8_t SiegeEngine::getUnitClass() {
    return UNIT_SIEGE_ENGINE;
}

double SiegeEngine::classAttackModifier(Object* enemy) {
    if (enemy->getGroupType() == BASE)
        return 2;

    if (enemy->getGroupType() == UNIT) {
        auto unit = static_cast<IUnit*>(enemy);
        if (unit->getUnitClass() == UNIT_MELEE) {
            return 0.4;
        }

        if (unit->getUnitClass() == UNIT_RANGED) {
            return 0.4;
        }

        if (unit->getUnitClass() == UNIT_SIEGE_ENGINE) {
            return 1;
        }
    }
    return 0;
}



/* CATAPULT CATAPULT CATAPULT CATAPULT CATAPULT CATAPULT CATAPULT CATAPULT CATAPULT CATAPULT */

Catapult::Catapult(Point point, Base* base) : SiegeEngine(point, base) {
    strength = Strength(60, 2);
    armor = Armor(5);
    health = Health(100, 100);
    movePoints = MovePoints(2, 2);
}

uint8_t Catapult::getObjectType() {
    return UNIT_CATAPULT;
}

double Catapult::typeAttackModifier(Object* enemy) {
    if (enemy->getGroupType() == BASE)
        return 1;

    if (enemy->getGroupType() == UNIT) {
        uint8_t enemyType = enemy->getObjectType();
        if (enemyType == UNIT_SWORDSMAN || enemyType == UNIT_PIKEMAN || enemyType == UNIT_CATAPULT || enemyType == UNIT_RAM)
            return 1.2;

        return 1;
    }
    return 0;
}



/* RAM RAM RAM RAM RAM RAM RAM RAM RAM RAM */

Ram::Ram(Point point, Base* base) : SiegeEngine(point, base) {
    strength = Strength(100, 0);
    armor = Armor(15);
    health = Health(100, 100);
    movePoints = MovePoints(2, 2);
}

uint8_t Ram::getObjectType() {
    return UNIT_RAM;
}

double Ram::typeAttackModifier(Object* enemy) {
    if (enemy->getGroupType() == BASE)
        return 1;

    if (enemy->getGroupType() == UNIT) {
        uint8_t enemyType = enemy->getObjectType();
        if (enemyType == UNIT_CATAPULT || enemyType == UNIT_RAM)
            return 2;

        return 1;
    }
    return 0;
}
