#include "IUnit.h"
#include "UnitGroup.h"
#include "Game/Game.h"
#include "Landscape/LandscapeHeader.h"
#include <typeinfo>


IUnit::IUnit() {}


uint8_t IUnit::getGroupType() {
    return UNIT;
}


bool IUnit::move(Point point) {
    if (Game::getInstance().getGameMediator().unitMove(this, point)) {
        setMovePoints(getMovePoints() - Game::getInstance().getGameMediator().getLandscape(point)->getMovementCost());
        setPoint(point);
        bool alive = Game::getInstance().getGameMediator().unitNeutralInterraction(this);
        if (alive) {
            Game::getInstance().unitWasMoved(this);
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

void IUnit::unite(IUnit* passive) {
    if (!Game::getInstance().getGameMediator().unitUnificationAccess(this, passive))
        return;

    if (typeid (*this) != typeid (UnitGroup) && typeid (*passive) != typeid (UnitGroup)) {
        setMovePoints(getMovePoints() - Game::getInstance().getGameMediator().getLandscape(getPoint())->getMovementCost());

        std::vector <Unit*> details;
        details.push_back(static_cast <Unit*> (this));
        details.push_back(static_cast <Unit*> (passive));

        new UnitGroup(details);
    }

    else if (typeid (*this) == typeid (UnitGroup) && typeid (*passive) != typeid (UnitGroup)) {
        UnitGroup* activeGroup = static_cast <UnitGroup*> (this);
        Unit* passiveUnit = static_cast <Unit*> (passive);

        if (activeGroup->getGroupSize() + 1 >= activeGroup->getMaxGroupSize())
            return;

        activeGroup->join(passiveUnit, true);
    }

    else if (typeid (*this) != typeid (UnitGroup) && typeid (*passive) == typeid (UnitGroup)) {
        Unit* activeUnit = static_cast <Unit*> (this);
        UnitGroup* passiveGroup = static_cast <UnitGroup*> (passive);

        if (passiveGroup->getGroupSize() + 1 >= passiveGroup->getMaxGroupSize())
            return;

        passiveGroup->join(activeUnit, false);
    }

    else if (typeid (*this) == typeid (UnitGroup) && typeid (*passive) == typeid (UnitGroup)) {
        UnitGroup* activeGroup = static_cast <UnitGroup*> (this);
        UnitGroup* passiveGroup = static_cast <UnitGroup*> (passive);

        if (activeGroup->getGroupSize() + passiveGroup->getGroupSize() > activeGroup->getMaxGroupSize())
            return;

        activeGroup->join(passiveGroup, true);
    }
}
