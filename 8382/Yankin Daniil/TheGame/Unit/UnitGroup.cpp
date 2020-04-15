#include "UnitGroup.h"
#include "Game/Game.h"
#include "Landscape/LandscapeHeader.h"
#include "Base/Base.h"


UnitGroup::UnitGroup(std::vector <Unit*> details) : maxGroupSize(4) {
    if (details.size() == 0)
        return;

    base = details.back()->getBase();
    uint8_t unitType = details.back()->getObjectType();
    uint8_t minMovePoints = details.back()->getMovePoints();
    Point point = details.back()->getPoint();

    while (unitSet.size() < maxGroupSize && details.size() > 0) {
        Unit* unit = details.back();
        details.pop_back();
        if (unit->getObjectType() != unitType)
            continue;

        minMovePoints = std::min(minMovePoints, unit->getMovePoints());
        unit->isGroup = true;
        unit->group = this;

        base->removeUnit(unit);
        Game::getInstance().objectWasDestructed(unit);

        unitSet.insert(unit);
    }

    setMovePoints(minMovePoints);
    setPoint(point);
    base->addUnit(this);
    Game::getInstance().objectWasCreated(static_cast <Object*> (this));
}

UnitGroup::~UnitGroup() {
    base->removeUnit(this);
    Game::getInstance().objectWasDestructed(static_cast <Object*> (this));
}



uint8_t UnitGroup::getUnitClass() {
    auto unit = unitSet.begin();
    return (*unit)->getUnitClass();
}

uint8_t UnitGroup::getObjectType() {
    auto unit = unitSet.begin();
    return (*unit)->getObjectType();
}



Point UnitGroup::getPoint() {
    auto unit = unitSet.begin();
    return (*unit)->getPoint();
}

void UnitGroup::setPoint(Point point) {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
       (*unit)->setPoint(point);
    }
}

Player* UnitGroup::getPlayer() {
    return base->getPlayer();
}

Base* UnitGroup::getBase() {
    return base;
}



uint16_t UnitGroup::getMaxHealth() {
    uint16_t maxHealthSum = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        maxHealthSum += (*unit)->getMaxHealth();
    }
    return maxHealthSum;
}

uint16_t UnitGroup::getHealth() {
    uint16_t healthSum = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        healthSum += (*unit)->getHealth();
    }
    return healthSum;
}

uint16_t UnitGroup::getAttack() {
    uint16_t strengthSum = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        strengthSum += (*unit)->getAttack();
    }
    return strengthSum * 0.85;
}

uint8_t UnitGroup::getAttackRadius() {
    auto unit = unitSet.begin();
    return (*unit)->getAttackRadius();
}

uint16_t UnitGroup::getArmor() {
    uint16_t armorSum = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        armorSum += (*unit)->getArmor();
    }
    return armorSum * 0.85;
}

uint8_t UnitGroup::getMaxMovePoints() {
    uint16_t maxMovePoints = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        if ((*unit)->getMaxMovePoints() < maxMovePoints || maxMovePoints == 0) {
            maxMovePoints = (*unit)->getMaxMovePoints();
        }
    }
    return maxMovePoints;
}

uint8_t UnitGroup::getMovePoints() {
    uint16_t maxMovePoints = getMaxMovePoints();

    uint16_t movePoints = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        if ((*unit)->getMovePoints() > movePoints) {
            movePoints = (*unit)->getMovePoints();
        }
    }
    return std::min(movePoints, maxMovePoints);
}

void UnitGroup::setMovePoints(uint8_t points) {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        (*unit)->setMovePoints(points);
    }
}



uint16_t UnitGroup::giveDamage(IUnit* enemy) {
    uint16_t damage = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        damage += (*unit)->giveDamage(enemy);
    }
    return damage;
}

uint16_t UnitGroup::giveDamage(Base* enemy) {
    uint16_t damage = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        damage += (*unit)->giveDamage(enemy);
    }
    return damage;
}

bool UnitGroup::takeDamage(uint16_t damage) {
    damage /= unitSet.size();
    std::vector <Unit*> diedUnits;

    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        bool alive = (*unit)->takeDamage(damage);
        if (!alive)
            diedUnits.push_back(*unit);
    }

    for (uint8_t i = 0; i < diedUnits.size(); i++) {
        unitSet.erase(diedUnits[i]);
    }

    if (unitSet.size() == 0) {
        delete this;
        return false;
    }
    return true;
}



void UnitGroup::join(Unit* unit, bool moveTo) {
    if (unitSet.size() > maxGroupSize && unit->getObjectType() != getObjectType())
        return;

    Game::getInstance().objectWasDestructed(unit);
    base->removeUnit(unit);

    if (moveTo) {
        move(unit->point);
    }
    else {
        unit->setMovePoints(unit->getMovePoints() - Game::getInstance().getGameMediator().getLandscape(getPoint())->getMovementCost());
    }

    unit->isGroup = true;
    unit->group = this;
    unit->point = getPoint();

    uint8_t minMovePoints = std::min(getMovePoints(), unit->getMovePoints());

    unitSet.insert(unit);

    setMovePoints(minMovePoints);
}

void UnitGroup::join(UnitGroup* group, bool moveTo) {
    if (unitSet.size() + group->getGroupSize() > maxGroupSize && group->getObjectType() != getObjectType())
        return;

    Game::getInstance().objectWasDestructed(group);
    base->removeUnit(group);

    if (moveTo) {
        move(group->getPoint());
    }
    else {
        group->setMovePoints(getMovePoints() - Game::getInstance().getGameMediator().getLandscape(getPoint())->getMovementCost());
    }

    uint8_t minMovePoints = std::min(getMovePoints(), group->getMovePoints());

    for (auto unit = group->unitSet.begin(); unit != group->unitSet.end(); unit++) {
        (*unit)->group = this;
        unitSet.insert(*unit);
    }

    setMovePoints(minMovePoints);
    group->unitSet.clear();
    delete group;
}



uint8_t UnitGroup::getMaxGroupSize() {
    return maxGroupSize;
}

uint8_t UnitGroup::getGroupSize() {
    return unitSet.size();
}



void UnitGroup::smallHeal(uint16_t healSize) {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++)
        (*unit)->smallHeal(healSize);
}

void UnitGroup::fullHeal() {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++)
        (*unit)->fullHeal();
}

void UnitGroup::attackModification(int16_t modSize) {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++)
        (*unit)->attackModification(modSize);
}

void UnitGroup::armorModification(int16_t modSize) {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++)
        (*unit)->armorModification(modSize);
}

void UnitGroup::renewMovePoints() {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++)
        (*unit)->renewMovePoints();
}
