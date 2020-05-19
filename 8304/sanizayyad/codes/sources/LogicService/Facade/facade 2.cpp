#include "facade.hpp"

Facade::Facade(std::shared_ptr<Mediator> mediator, std::shared_ptr<Base> homeBase,
               std::shared_ptr<std::set<std::shared_ptr<Unit>>> units,
               std::shared_ptr<Base> enemyBase,
               std::shared_ptr<BattleField> battleField)
{
    this->homeBase = homeBase;
    this->mediator = mediator;
    this->units = units;
    this->enemyBase = enemyBase;
    this->battleField = battleField;
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

std::shared_ptr<Unit> Facade::createUnit(std::string type){
    auto enemyBasePosition = enemyBase->getPosition();
    auto homeBasePosition = homeBase->getPosition();
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

    if (homeBasePosition.x < enemyBasePosition.x) {
        dx++;
    }
    else {
        dx--;
    }
    
    
    if(type == "short"){
       return homeBase->createShortRangeUnit(dx, dy);
    }
    else if(type == "long"){
        return homeBase->createLongRangeUnit(dx, dy);
    }else{
        return homeBase->createDynamicRangeUnit(dx, dy);
    }
    
    return NULL;
}

bool Facade::createShortRangeUnit()
{

    auto unit = createUnit("short");
    if (unit) {
        units->insert(unit);
        battleField->addUnit(unit);
        return true;
    }
    return false;
}


bool Facade::createLongRangeUnit()
{
     auto unit = createUnit("long");
        if (unit) {
            units->insert(unit);
            battleField->addUnit(unit);
            return true;
        }
        return false;
}


bool Facade::createDynamicRangeUnit()
{
     auto unit = createUnit("dynamic");
        if (unit) {
            units->insert(unit);
            battleField->addUnit(unit);
            return true;
        }
        return false;
}


bool Facade::attack(std::shared_ptr<Unit> unit)
{
    auto unitPosition = unit->getPosition();
    auto weapon = unit->getWeapon();
    auto dist = static_cast<int>(weapon->getDistanceAttack());
    auto player = unit->getPlayer();

    for (int i = unitPosition.y - dist; i <= unitPosition.y + dist; ++i) {
        for (int j = unitPosition.x - dist; j <= unitPosition.x + dist; ++j) {
            if (j < battleField->getWidth() && j >= 0 && i < battleField->getHeight() && i >= 0) {
                if (sqrt(pow(i - unitPosition.y, 2) + pow(j - unitPosition.x, 2)) <= dist) {
                    auto cell = battleField->getFieldCell(Position2D(j, i));
                    if (!cell->isEmpty()) {
                        auto enemy = cell->getUnit();
                        if (enemy->getPlayer() != player) {
                            enemy->makeDamage(weapon->getDamage() *enemy->getArmor()->getResistance());
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}


void Facade::moveUnit(std::shared_ptr<Unit> unit)
{
    auto enemyBasePosition = enemyBase->getPosition();
    auto unitPosition = unit->getPosition();

    if (unitPosition.x < enemyBasePosition.x) {
        unit->moveRight();
    }
    else {
        unit->moveLeft();
    }

   
    if (unitPosition.y < enemyBasePosition.y) {
        unit->moveBottom();
    }
    else if (unitPosition.y > enemyBasePosition.y) {
        unit->moveTop();
    }
    
}
