#include "GameMediator.h"
#include "Game.h"
#include "Landscape/LandscapeHeader.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"
#include <Neutrals/NeutralContext.h>
#include <math.h>


GameMediator::GameMediator(Game* game) {
    this->game = game;
}


bool GameMediator::unitMove(IUnit* unit, Point point) {
    if (!checkNeighborPoint(unit->getPoint(), point))
        return false;

    if (!game->field->isUnitFree(point) || (!game->field->isBuildingFree(point) && game->field->getBuildingGroupType(point) == BASE &&
                                                                                   game->field->getBase(point)->getPlayer() != unit->getPlayer()))
        return false;

    ILandscape* land = game->field->getLandscape(point);
    if (!land->movementAccess())
        return false;

    if (unit->getMovePoints() < land->getMovementCost())
        return false;

    Point oldPoint = unit->getPoint();
    game->field->removeUnit(unit->getPoint());
    game->field->setUnit(point, unit);
    game->getGameFacade().setVisualUnitPos(unit);

    std::vector<int> logParameters = {unit->getObjectType(), oldPoint.getX(), oldPoint.getY(), unit->getPlayer()->getColor(),
                                          point.getX(), point.getY()};
    game->logAdapter->log(LOG_MOVE, logParameters);

    return true;
}

bool GameMediator::unitNeutralInterraction(IUnit* unit) {
    Point point = unit->getPoint();
    if (game->field->isBuildingFree(point) || game->field->getBuildingGroupType(point) != NEUT_OBJECT)
        return true;

    NeutralContext* context = game->field->getContext(point);
    uint8_t type = unit->getObjectType();
    if (type == UNIT_SWORDSMAN || type == UNIT_PIKEMAN)
        context->setStrategy(new HealOffice);
    else if (type == UNIT_SCOUT_CAVALRY || type == UNIT_SCOUT_CAVALRY)
        context->setStrategy(new MovementOffice);
    else if (type == UNIT_ARCHER || type == UNIT_CROSSBOWMAN)
        context->setStrategy(new ArmorOffice);
    else
        context->setStrategy(new DamageOffice);

    bool alive = *context >> *unit;
    return alive;
}

void GameMediator::unitAttack(IUnit* attacker, IUnit* defender) {
    if (attacker->getAttackRadius() == 0) {
        if (!checkNeighborPoint(attacker->getPoint(), defender->getPoint()))
            return;

        if (attacker->getMovePoints() < getLandscape(defender->getPoint())->getMovementCost())
            return;

        Point defenderPoint = defender->getPoint();

        uint16_t attackerDamage = attacker->giveDamage(defender);
        uint16_t defenderDamage = defender->giveDamage(attacker);

        std::vector<int> attLogParameters = {attacker->getObjectType(), attacker->getPoint().getX(), attacker->getPoint().getY(), attacker->getPlayer()->getColor(),
                                               defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor(),
                                               attackerDamage};
        std::vector<int> defLogParameters = {defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor(),
                                               attacker->getObjectType(), attacker->getPoint().getX(), attacker->getPoint().getY(), attacker->getPlayer()->getColor(),
                                               defenderDamage};

        game->logAdapter->log(LOG_ATTACK, attLogParameters);
        bool defenderALive = defender->takeDamage(attackerDamage);

        game->logAdapter->log(LOG_DEFEND, defLogParameters);
        bool attackerALive = attacker->takeDamage(defenderDamage);

        if (!defenderALive && attackerALive) {
            attacker->move(defenderPoint);
        }

        if (attackerALive) {
            game->getGameFacade().setVisualUnitPos(attacker);
        }

        return;
    }
    else {
        if (attacker->getAttackRadius() < distance(attacker->getPoint(), defender->getPoint()))
            return;

        uint16_t attackerDamage = attacker->giveDamage(defender);

        std::vector<int> logParameters = {attacker->getObjectType(), attacker->getPoint().getX(), attacker->getPoint().getY(), attacker->getPlayer()->getColor(),
                                               defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor(),
                                               attackerDamage};
        game->logAdapter->log(LOG_ATTACK, logParameters);

        defender->takeDamage(attackerDamage);
        return;
    }
}

void GameMediator::unitAttack(IUnit* attacker, Base* defender) {
    if (attacker->getAttackRadius() == 0) {
        if (!checkNeighborPoint(attacker->getPoint(), defender->getPoint()))
            return;

        if (attacker->getMovePoints() < getLandscape(defender->getPoint())->getMovementCost())
            return;

        Point defenderPoint = defender->getPoint();

        uint16_t attackerDamage = attacker->giveDamage(defender);
        uint16_t defenderDamage = defender->giveDamage(attacker);

        std::vector<int> attLogParameters = {attacker->getObjectType(), attacker->getPoint().getX(), attacker->getPoint().getY(), attacker->getPlayer()->getColor(),
                                               defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor(),
                                               attackerDamage};
        std::vector<int> defLogParameters = {defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor(),
                                               attacker->getObjectType(), attacker->getPoint().getX(), attacker->getPoint().getY(), attacker->getPlayer()->getColor(),
                                               defenderDamage};

        game->logAdapter->log(LOG_ATTACK, attLogParameters);
        bool defenderALive = defender->takeDamage(attackerDamage);

        game->logAdapter->log(LOG_DEFEND, defLogParameters);
        bool attackerALive = attacker->takeDamage(defenderDamage);

        if (!defenderALive && attackerALive) {
            attacker->move(defenderPoint);
        }

        if (attackerALive) {
            game->getGameFacade().setVisualUnitPos(attacker);
        }

        return;
    }
    else {
        if (attacker->getAttackRadius() < distance(attacker->getPoint(), defender->getPoint()))
            return;

        uint16_t attackerDamage = attacker->giveDamage(defender);

        std::vector<int> logParameters = {attacker->getObjectType(), attacker->getPoint().getX(), attacker->getPoint().getY(), attacker->getPlayer()->getColor(),
                                          defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor(),
                                          attackerDamage};
        game->logAdapter->log(LOG_ATTACK, logParameters);

        defender->takeDamage(attackerDamage);

        return;
    }
}

bool GameMediator::unitUnificationAccess(IUnit* active, IUnit* passive) {
    if (!checkNeighborPoint(active->getPoint(), passive->getPoint()))
        return false;
    if (active->getMovePoints() < game->field->getLandscape(passive->getPoint())->getMovementCost())
        return false;
    return true;
}

bool GameMediator::baseProductionAccess(Base *base) {
    Point basePoint = base->getPoint();
    return (game->field->isUnitFree(basePoint) && base->isBelowUnitMax());
}


bool GameMediator::checkNeighborPoint(Point point, Point supposeNeighbor) {
    uint16_t x = point.getX();
    uint16_t y = point.getY();

    if (Point(x-1, y) == supposeNeighbor || Point(x+1, y) == supposeNeighbor || Point(x, y-1) == supposeNeighbor || Point(x, y+1) == supposeNeighbor)
        return true;

    if (y % 2 == 0) {
        if (Point(x-1, y+1) == supposeNeighbor || Point(x-1, y-1) == supposeNeighbor)
            return true;
    }
    else {
        if (Point(x+1, y+1) == supposeNeighbor || Point(x+1, y-1) == supposeNeighbor)
            return true;
    }

    return false;
}

uint16_t GameMediator::distance(Point one, Point two) {
    uint16_t xDiff = std::abs(one.getX() - two.getX());
    uint16_t yDiff = std::abs(one.getY() - two.getY());


    if (static_cast<int>(one.getX()) - static_cast<int>(two.getX()) >= 0) {
        if (one.getY() % 2 == 0) {
            yDiff = std::max(yDiff - static_cast<int>(std::floor(xDiff / 2)), 0);
        }
        else {
            yDiff = std::max(yDiff - static_cast<int>(std::ceil(xDiff / 2)), 0);
        }
    }
    else if (static_cast<int>(one.getX()) - static_cast<int>(two.getX()) < 0) {
        if (one.getY() % 2 == 0) {
            yDiff = std::max(yDiff - static_cast<int>(std::floor(xDiff / 2)), 0);
        }
        else {
            yDiff = std::max(yDiff - static_cast<int>(std::ceil(xDiff / 2)), 0);
        }
    }

    return xDiff+yDiff;
}

ILandscape* GameMediator::getLandscape(Point point) {
    return game->field->getLandscape(point);
}
