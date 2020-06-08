//
// Created by therealyou on 01.06.2020.
//

#include "SnapShot.h"

SnapShot::SnapShot(GameField *gameField, Base *Base1, Base *Base2, Base *Base3, Unit *Unit1, Unit *Unit2, Unit *Unit3,
                   Adapter *adapter1, int gameMode1) :
        gameField(gameField), height(gameField->getHeight()),
        width(gameField->getWidth()), base1(Base1),
        base2(Base2), base3(Base3), unit1(Unit1), unit2(Unit2),
        unit3(Unit3), adapter(adapter1), gameMode(gameMode1) {
    outStream = new std::ofstream;
    outStream->open("save.txt");
}

SnapShot::SnapShot(GameField *tmp) : gameField(tmp) {
    inStream = new std::ifstream;
    inStream->open("save.txt");
}

SnapShot::~SnapShot() {
    if (outStream) {
        outStream->close();
        delete outStream;
    }
    if (inStream) {
        inStream->close();
        delete inStream;
    }
}

void SnapShot::save() {
    std::string str;
    *outStream << std::to_string(gameMode) << std::endl;
    *outStream << width << " " << height << std::endl;
    std::cout << width << " " << height << std::endl;
//    *outStream << str;
    if (gameMode == 1) {
        if (base1) {
            str = base1->getBaseInfo();
            *outStream << str << std::endl;
            str = base1->getUnitsInfo();
            *outStream << str << std::endl;
        }
        if (base2) {
            *outStream << "." << std::endl;
            str = base2->getBaseInfo();
            *outStream << str << std::endl;
            str = base2->getUnitsInfo();
            *outStream << str << std::endl;
        }
        if (base3) {
            *outStream << "." << std::endl;
            str = base3->getBaseInfo();
            *outStream << str << std::endl;
            str = base3->getUnitsInfo();
            *outStream << str << std::endl;
        }
    } else {
        *outStream << (!unit3 ? "2" : "3") << std::endl;
        *outStream << unit1->getInfo() << std::endl;
        *outStream << unit2->getInfo() << std::endl;
        if (unit3)
            *outStream << unit3->getInfo() << std::endl;
    }
    adapter->save();
}

void SnapShot::load() {
    int x, y, mode, maxUnits, health, currentUnitCount;
    ProfileUnit values;
    std::string unitName, str;
    int unitClass;
    adapter = new Adapter();
    *inStream >> mode;
    if (inStream->fail())
        throw TypeException("int");
    if (mode != 1 && mode != 2)
        throw LogicException("incorrect mode! Request is: ", mode);
    *inStream >> x >> y;
    if (inStream->fail())
        throw TypeException("int");
    if (x <= 0)
        throw LogicException("incorrect gameField size: ", x);
    if (y <= 0)
        throw LogicException("incorrect gameField size: ", y);
    GameField newField(x, y, adapter, mode);

    if (mode == 1) {
        *inStream >> x >> y >> health >> maxUnits >> currentUnitCount;
        if (inStream->fail())
            throw TypeException("int");
        if (newField.getWidth() < x || x < 0)
            throw LogicException("incorrect base 1 coordinate x ", x);
        if (newField.getHeight() < y || y < 0)
            throw LogicException("incorrect base 1 coordinate y ", y);
        if (health <= 0)
            throw LogicException("incorrect base 1 health value ", health);
        if (maxUnits <= 0)
            throw LogicException("incorrect base 1 maxUnits value ", maxUnits);
        if (currentUnitCount < 0 || currentUnitCount > maxUnits)
            throw LogicException("incorrect base 1 maxUnits value ", maxUnits);
        base1 = newField.createBase(x, y, 1, maxUnits, health);

        ///
        for (size_t i = 0; i < currentUnitCount; i++) {
            *inStream >> unitClass >> values.id >> x >> y >> values.health >> values.armor >> values.damage
                      >> values.attackRange >> values.speed;
            if (inStream->fail())
                throw TypeException("char(aka int) int int int double double double int double");
            if (unitClass != 'E' && unitClass != 'G' && unitClass != 'P' && unitClass != 'T' && unitClass != 'S' &&
                unitClass != 'W')
                throw LogicException("nonexistent class", unitClass);
            if (newField.getWidth() < x || x < 0)
                throw LogicException("incorrect unit coordinate x", x);
            if (newField.getHeight() < y || y < 0)
                throw LogicException("incorrect unit coordinate y ", y);
            if (values.health <= 0)
                throw LogicException("incorrect unit health value ", values.health);
            if (values.armor < 0)
                throw LogicException("incorrect unit armor value ", values.armor);
            if (values.damage <= 0)
                throw LogicException("incorrect unit attack value ", values.damage);
            if (values.attackRange <= 0)
                throw LogicException("incorrect unit attackRange value ", values.attackRange);
            if (values.speed <= 0)
                throw LogicException("incorrect unit speed value ", values.speed);
            newField.base1->createUnit(static_cast<char >(unitClass), x, y, values);
        }

        *inStream >> str;
        if (inStream->fail()) {
            throw TypeException("incorrect file state");
        }
        if (str != ".")
            throw CheckException(str);

        // base 2
        *inStream >> x >> y >> health >> maxUnits >> currentUnitCount;
        if (inStream->fail())
            throw TypeException("int");
        if (newField.getWidth() < x || x < 0)
            throw LogicException("incorrect base 2 coordinate x ", x);
        if (newField.getHeight() < y || y < 0)
            throw LogicException("incorrect base 2 coordinate y ", y);
        if (health <= 0)
            throw LogicException("incorrect base 2 health value ", health);
        if (maxUnits <= 0)
            throw LogicException("incorrect base 2 maxUnits value ", maxUnits);
        if (currentUnitCount < 0 || currentUnitCount > maxUnits)
            throw LogicException("incorrect base 2 maxUnits value ", maxUnits);
        base2 = newField.createBase(x, y, 2, maxUnits, health);

        ///
        for (size_t i = 0; i < currentUnitCount; i++) {
            *inStream >> unitClass >> values.id >> x >> y >> values.health >> values.armor >> values.damage
                      >> values.attackRange >> values.speed;
            if (inStream->fail())
                throw TypeException("char(aka int) int int int double double double int double");
            if (unitClass != 'E' && unitClass != 'G' && unitClass != 'P' && unitClass != 'T' && unitClass != 'S' &&
                unitClass != 'W')
                throw LogicException("nonexistent class", unitClass);
            if (newField.getWidth() < x || x < 0)
                throw LogicException("incorrect unit coordinate x", x);
            if (newField.getHeight() < y || y < 0)
                throw LogicException("incorrect unit coordinate y ", y);
            if (values.health <= 0)
                throw LogicException("incorrect unit health value ", values.health);
            if (values.armor < 0)
                throw LogicException("incorrect unit armor value ", values.armor);
            if (values.damage <= 0)
                throw LogicException("incorrect unit attack value ", values.damage);
            if (values.attackRange <= 0)
                throw LogicException("incorrect unit attackRange value ", values.attackRange);
            if (values.speed <= 0)
                throw LogicException("incorrect unit speed value ", values.speed);
            newField.base2->createUnit(static_cast<char >(unitClass), x, y, values);
        }

        *inStream >> str;
        if (inStream->eof()) {
            newField.printField();
            *(this->gameField) = newField;
            adapter->load();
            return;
        }
        if (inStream->fail()) {
            throw TypeException("incorrect file state");
        }
        if (str != ".")
            throw CheckException(str);
        // base3
        std::cout << str + "\n";
        *inStream >> x >> y >> health >> maxUnits >> currentUnitCount;
        if (inStream->fail())
            throw TypeException("int");
        if (newField.getWidth() < x || x < 0)
            throw LogicException("incorrect base 3 coordinate x ", x);
        if (newField.getHeight() < y || y < 0)
            throw LogicException("incorrect base 3 coordinate y ", y);
        if (health <= 0)
            throw LogicException("incorrect base 3 health value ", health);
        if (maxUnits <= 0)
            throw LogicException("incorrect base 3 maxUnits value ", maxUnits);
        if (currentUnitCount < 0 || currentUnitCount > maxUnits)
            throw LogicException("incorrect base 3 maxUnits value ", maxUnits);
        base3 = newField.createBase(x, y, 3, maxUnits, health);

        ///
        for (size_t i = 0; i < currentUnitCount; i++) {
            *inStream >> unitClass >> values.id >> x >> y >> values.health >> values.armor >> values.damage
                      >> values.attackRange >> values.speed;
            if (inStream->fail())
                throw TypeException("string char int int int int int int");
            if (unitClass != 'E' && unitClass != 'G' && unitClass != 'P' && unitClass != 'T' && unitClass != 'S' &&
                unitClass != 'W')
                throw LogicException("nonexistent class", unitClass);
            if (newField.getWidth() < x || x < 0)
                throw LogicException("incorrect unit coordinate x", x);
            if (newField.getHeight() < y || y < 0)
                throw LogicException("incorrect unit coordinate y ", y);
            if (values.health <= 0)
                throw LogicException("incorrect unit health value ", values.health);
            if (values.armor < 0)
                throw LogicException("incorrect unit armor value ", values.armor);
            if (values.damage <= 0)
                throw LogicException("incorrect unit attack value ", values.damage);
            if (values.attackRange <= 0)
                throw LogicException("incorrect unit attackRange value ", values.attackRange);
            newField.base3->createUnit(unitClass, x, y, values);
        }

        *inStream >> str;
        if (!inStream->eof())
            throw CheckException("non end");


    } else {
        int playersNumber;
        *inStream >> playersNumber;
        if (inStream->fail())
            throw TypeException("int");
        if (playersNumber != 2 && playersNumber != 3)
            throw LogicException("incorrect players number", playersNumber);

        *inStream >> unitClass >> values.id >> x >> y >> values.health >> values.armor >> values.damage
                  >> values.attackRange >> values.speed;
        if (inStream->fail())
            throw TypeException("string char int int int int int int");
        if (unitClass != 'E' && unitClass != 'G' && unitClass != 'P' && unitClass != 'T' && unitClass != 'S' &&
            unitClass != 'W')
            throw LogicException("nonexistent class", unitClass);
        if (newField.getWidth() < x || x < 0)
            throw LogicException("incorrect unit coordinate x", x);
        if (newField.getHeight() < y || y < 0)
            throw LogicException("incorrect unit coordinate y ", y);
        if (values.health <= 0)
            throw LogicException("incorrect unit health value ", values.health);
        if (values.armor < 0)
            throw LogicException("incorrect unit armor value ", values.armor);
        if (values.damage <= 0)
            throw LogicException("incorrect unit attack value ", values.damage);
        if (values.attackRange <= 0)
            throw LogicException("incorrect unit attackRange value ", values.attackRange);
        Unit *unit = Fabric().createUnit(unitClass, values);
        newField.addUnit(unit, x, y);
        newField.unit1 = unit;

        *inStream >> unitClass >> values.id >> x >> y >> values.health >> values.armor >> values.damage
                  >> values.attackRange >> values.speed;
        if (inStream->fail())
            throw TypeException("string char int int int int int int");
        if (unitClass != 'E' && unitClass != 'G' && unitClass != 'P' && unitClass != 'T' && unitClass != 'S' &&
            unitClass != 'W')
            throw LogicException("nonexistent class", unitClass);
        if (newField.getWidth() < x || x < 0)
            throw LogicException("incorrect unit coordinate x", x);
        if (newField.getHeight() < y || y < 0)
            throw LogicException("incorrect unit coordinate y ", y);
        if (values.health <= 0)
            throw LogicException("incorrect unit health value ", values.health);
        if (values.armor < 0)
            throw LogicException("incorrect unit armor value ", values.armor);
        if (values.damage <= 0)
            throw LogicException("incorrect unit attack value ", values.damage);
        if (values.attackRange <= 0)
            throw LogicException("incorrect unit attackRange value ", values.attackRange);
        unit = Fabric().createUnit(unitClass, values);
        newField.addUnit(unit, x, y);
        newField.unit2 = unit;

        if (playersNumber == 2) {
            *inStream >> str;
            if (!inStream->eof())
                throw CheckException("non end");
            *(this->gameField) = newField;
            gameField->printField();
            adapter->load();
            return;
        }

        *inStream >> unitClass >> values.id >> x >> y >> values.health >> values.armor >> values.damage
                  >> values.attackRange >> values.speed;
        if (inStream->fail())
            throw TypeException("string char int int int int int int");
        if (unitClass != 'E' && unitClass != 'G' && unitClass != 'P' && unitClass != 'T' && unitClass != 'S' &&
            unitClass != 'W')
            throw LogicException("nonexistent class", unitClass);
        if (newField.getWidth() < x || x < 0)
            throw LogicException("incorrect unit coordinate x", x);
        if (newField.getHeight() < y || y < 0)
            throw LogicException("incorrect unit coordinate y ", y);
        if (values.health <= 0)
            throw LogicException("incorrect unit health value ", values.health);
        if (values.armor < 0)
            throw LogicException("incorrect unit armor value ", values.armor);
        if (values.damage <= 0)
            throw LogicException("incorrect unit attack value ", values.damage);
        if (values.attackRange <= 0)
            throw LogicException("incorrect unit attackRange value ", values.attackRange);
        unit = Fabric().createUnit(unitClass, values);
        newField.addUnit(unit, x, y);
        newField.unit3 = unit;
        *inStream >> str;
        if (!inStream->eof())
            throw CheckException("non end");
    }
    newField.printField();
    *(this->gameField) = newField;
    adapter->load();
}