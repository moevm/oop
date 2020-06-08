//
// Created by therealyou on 09.03.2020.
//

#include "Base.h"

Unit *Base::createUnit(char unit, int x, int y, ProfileUnit value) {
    UnitsType unitType;
    unit = std::tolower(unit);
    switch (unit) {
        case 'e':
            unitType = UnitsType::ELF;
            break;
        case 'g':
            unitType = UnitsType::GOBLIN;
            break;
        case 'p':
            unitType = UnitsType::PEON;
            break;
        case 's':
            unitType = UnitsType::SHOOTER;
            break;
        case 't':
            unitType = UnitsType::TROLL;
            break;
        case 'w':
            unitType = UnitsType::WITCH;
            break;
        default:
            std::cerr << "\t\tUnknown type of unit" << std::endl;
    }
    Unit *tempUnit;
    switch (unitType) {
        case UnitsType::ELF:
            tempUnit = FactoryOfMagicians().createElf();
            break;
        case UnitsType::GOBLIN:
            tempUnit = FactoryOfOrcs().createGoblin();
            break;
        case UnitsType::PEON:
            tempUnit = FactoryOfAlliance().createPeon();
            break;
        case UnitsType::SHOOTER:
            tempUnit = FactoryOfAlliance().createShooter();
            break;
        case UnitsType::TROLL:
            tempUnit = FactoryOfOrcs().createTroll();
            break;
        case UnitsType::WITCH:
            tempUnit = FactoryOfMagicians().createWitch();
            break;
        default:
            std::cerr << "\t\tUnknown type of unit" << std::endl;
    }
    tempUnit->profileUnit = value;
    tempUnit->addObserver(this);
    tempUnit->setX(x);
    tempUnit->setY(y);
    units.push_back(tempUnit);
    countUnits++;
    gameField->addUnit(tempUnit, x, y);
    return tempUnit;
};

Unit *Base::createUnit(UnitsType unit, int x, int y, int unitId) {
//    if (countUnits == maxCountUnits) {
//        std::cerr << "\t\tLimit of units" << std::endl;
//        return nullptr;
//    }
    Unit *tempUnit;
    switch (unit) {
        case UnitsType::ELF:
            tempUnit = FactoryOfMagicians().createElf();
            break;
        case UnitsType::GOBLIN:
            tempUnit = FactoryOfOrcs().createGoblin();
            break;
        case UnitsType::PEON:
            tempUnit = FactoryOfAlliance().createPeon();
            break;
        case UnitsType::SHOOTER:
            tempUnit = FactoryOfAlliance().createShooter();
            break;
        case UnitsType::TROLL:
            tempUnit = FactoryOfOrcs().createTroll();
            break;
        case UnitsType::WITCH:
            tempUnit = FactoryOfMagicians().createWitch();
            break;
        default:
            throw LogicException("non-exist unit class", std::to_string(unit));
    }
    tempUnit->addObserver(this);
    tempUnit->setX(x);
    tempUnit->setY(y);
    std::cout << units.size() << std::endl;
    units.push_back(tempUnit);
    std::cout << units.size() << std::endl;
    countUnits++;
    tempUnit->profileUnit.id = unitId;
    gameField->addUnit(tempUnit, x, y);
    return tempUnit;
}

Base::Base(GameField *gameField, int x, int y, int baseNumber, int maxCountUnits, int health) :
        x(x), y(y), baseNumber(baseNumber),
        maxCountUnits(maxCountUnits),
        health(health),
        gameField(gameField),
        countUnits(0),
        savingCounter(0) {
    units.clear();
};

void Base::print(bool full) const {
    std::cout << "┌──────────────────────────────" << std::endl
              << "│ This base: [health=" << health <<
              ", countUnits=" << countUnits <<
              ", maxCountUnits=" << maxCountUnits << "]" << std::endl << "│ UnitsType : ";
    if (full) {
        std::cout << std::endl;
    }
    std::cout << "[ ";
    for (auto unit : units) {
        if (!full) {
            std::cout << unit->getCharType() << " ";
        } else {
            std::cout << *unit;
        }
    }
    std::cout << "]";
    std::cout << std::endl << "└──────────────────────────────" << std::endl;
}

void Base::update(SubjectObserve *subjectObserve) {
    deleteUnit((Unit *) subjectObserve);
}

void Base::deleteUnit(Unit *unit) {
    unit->removeObserver(this);
    auto iter = units.begin();
    while (iter != units.end()) {
        if (*iter == unit) {
            units.erase(iter);
            break;
        }
        iter++;
    }
    countUnits--;
}

void Base::getDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        gameField->deleteBase(this);
    }
}


const std::vector<Unit *> &Base::getUnits() const {
    return units;
}

std::ostream &operator<<(std::ostream &out, const Base &base) {
    out << "┌──────────────────────────────" << std::endl
        << "│ This base: [health=" << base.health <<
        ", countUnits=" << base.countUnits <<
        ", maxCountUnits=" << base.maxCountUnits << "]" << std::endl << "│ UnitsType : ";
    out << std::endl;
    out << "[ ";
    for (auto& unit : base.units) {
        out << *unit;
    }
    out << "]";
    out << std::endl << "└──────────────────────────────" << std::endl;

    return out;
}

std::string Base::getUnitsInfo() {
    std::string unitInfo;
    for (auto& unit : units) {
        unitInfo += unit->getInfo();
        unitInfo += '\n';
    }
    if (unitInfo.length() > 0) {
        unitInfo.erase(unitInfo.size() - 1);
    }
    return unitInfo;
}

std::string Base::getBaseInfo() const {
    std::string baseInfo = std::to_string(x) + " " + std::to_string(y)
                           + " " + std::to_string(health)
                           + " " + std::to_string(maxCountUnits)
                           + " " + std::to_string(countUnits);
    return baseInfo;
}

Unit *Base::findUnit(int unitId) {
    for (auto& unit : units){
        if (unit->getId() == unitId){
            return unit;
        }
    }
    return nullptr;
}

std::vector<Unit *> Base::getUnits() {
    return units;
}
