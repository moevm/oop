#include "facade.h"


Facade::Facade(Mediator* mediator,
               Base* base,
               std::set<Unit* >* units,
               Base* enemyBase,
               GameField* gameField)
{
    this->base = base;
    this->mediator = mediator;
    this->units = units;
    this->enemyBase = enemyBase;
    this->gameField = gameField;
}


Facade::~Facade()
{
    delete base;
    delete mediator;
    delete units;
    delete enemyBase;
    delete base;
}


void Facade::charge()
{
    for (auto unit : *units) {
        if (!attack(unit)) {
            moveUnit(unit);
        }
    }
}


void Facade::deffend()
{
    for (auto unit : *units) {
        attack(unit);
    }
}


bool Facade::createInfantryUnit()
{
    auto posEnemy = enemyBase->getCoordiante();
    auto posBase = base->getCoordiante();
    srand(time(0));

    int dx = 0;
    int dy = 0;
    auto choose = rand() % 3;

    switch (choose) {
    case 1:
        dy++;
        break;
    case 2:
        dy--;
        break;
    }

    if (posBase.x < posEnemy.x) {
        dx += 1;
    }
    else {
        dx -= 1;
    }

    auto unit = base->createInfantryUnit(dx, dy);
    if (unit!= nullptr) {
        unit->setPlayer(base->getPlayer());
    }
    if (unit) {
        units->insert(unit);
        gameField->addUnit(unit);
        return true;
    }

    return false;
}


bool Facade::createStandingUnit()
{
    auto posEnemy = enemyBase->getCoordiante();
    auto posBase = base->getCoordiante();
    srand(time(0));

    int dx = 0;
    int dy = 0;
    auto choose = rand() % 3;

    switch (choose) {
    case 1:
        dy++;
        break;
    case 2:
        dy--;
        break;
    }

    if (posBase.x < posEnemy.x) {
        dx++;
    }
    else {
        dx--;
    }

    auto unit = base->createStandingUnit(dx, dy);

    if (unit != nullptr){
        unit->setPlayer(base->getPlayer());
    }

    if (unit) {
        units->insert(unit);
        gameField->addUnit(unit);
        return true;
    }

    return false;
}


bool Facade::createFlyingUnit()
{
    auto posEnemy = enemyBase->getCoordiante();
    auto posBase = base->getCoordiante();
    srand(time(0));

    int dx = 0;
    int dy = 0;
    auto choose = rand() % 3;

    switch (choose) {
    case 1:
        dy++;
        break;
    case 2:
        dy--;
        break;
    }

    if (posBase.x < posEnemy.x) {
        dx += 1;
    }
    else {
        dx -= 1;
    }

    auto unit = base->createFlyingUnit(dx, dy);
    if (unit!= nullptr) {
        unit->setPlayer(base->getPlayer());
    }
    if (unit) {
        units->insert(unit);
        gameField->addUnit(unit);
        return true;
    }

    return false;
}


bool Facade::attack(Unit* unit)
{
    auto posUnit = unit->getCoordiante();
    auto weapon = unit->getWeapon();
    auto dist = weapon->getDistance();
    auto player = unit->getPlayer();

    for (size_t i = posUnit.y - dist; i <= posUnit.y + dist; ++i) {
        for (size_t j = posUnit.x - dist; j <= posUnit.x + dist; ++j) {
            if (j < gameField->getWidth() && j >= 0 && i < gameField->getHeight() &&
                    i >= 0) {
                auto cell = gameField->getCell(j, i);//getCell(Point2D(j, i));
                if (!cell->isEmpty()) {
                    auto enemy = cell->getUnit();
                    if (enemy->getPlayer() != player) {
                        enemy->toHurt(weapon->getDamage() * enemy->getArmor()->getResistance());
                        return true;
                    }
                }
            }
        }
    }

    return false;
}


void Facade::moveUnit(Unit* unit)
{

    auto posEnemy = enemyBase->getCoordiante();
    auto posUnit = unit->getCoordiante();

    if (posUnit.x < posEnemy.x) {
        unit->move(1, 0);
    }
    else {
        unit->move(-1, 0);
    }

    if (!unit->isFlying()) {
        if (posUnit.y < posEnemy.y) {
            unit->move(0, 1);
        }
        else if (posUnit.y > posEnemy.y) {
            unit->move(0, -1);
        }
    }
    else {
        auto tmpPos = (posUnit.x + gameField->getWidth() / 2) / 2;
        if (posUnit.x < posEnemy.x) {
            if (tmpPos <= gameField->getWidth() / 2) {
                if (posUnit.y < gameField->getHeight() / 2 &&
                        posUnit.y > gameField->getHeight() / 4) {
                    unit->move(0, -1);
                }
                else if (posUnit.y >= gameField->getHeight() / 2 &&
                         posUnit.y < 3 * gameField->getHeight() / 4) {
                    unit->move(0, 1);
                }
            }
            else {
                if (posUnit.y < posEnemy.y) {
                    unit->move(0, 1);
                }
                else {
                    unit->move(0, -1);
                }
            }
        }
        else {
            if (tmpPos >= gameField->getWidth() / 2) {
                if (posUnit.y < gameField->getHeight() / 2 &&
                        posUnit.y > gameField->getHeight() / 4) {
                    unit->move(0, -1);
                }
                else if (posUnit.y >= gameField->getHeight() / 2 &&
                         posUnit.y < 3 * gameField->getHeight() / 4) {
                    unit->move(0, 1);
                }
            }
            else {
                if (posUnit.y < posEnemy.y) {
                    unit->move(0, 1);
                }
                else {
                    unit->move(0, -1);
                }
            }
        }
    }
}
