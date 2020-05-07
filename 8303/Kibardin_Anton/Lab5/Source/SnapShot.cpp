//
// Created by user on 03.05.2020.
//

#include "SnapShot.h"

SnapShot::SnapShot(Field *tmp, Base* Base1,Base* Base2,Base* Base3, Unit* Unit1, Unit* Unit2, Adapter* adapter1, int gameMode1):/*field(tmp),*/ X(tmp->getX()), Y(tmp->getY())
, base1(Base1), base2(Base2), base3(Base3), unit1(Unit1), unit2(Unit2), adapter(adapter1), gameMode(gameMode1){
    outStream = new std::ofstream;
    outStream->open("save.txt");
}

SnapShot::SnapShot(Field* tmp):field(tmp){
    inStream = new std::ifstream;
    inStream->open("save.txt");
}

SnapShot::~SnapShot() {
    puts("snap clear");
    if(outStream)
    {
        outStream->close();
        delete outStream;
    }
    if(inStream)
    {
        inStream->close();
        delete inStream;
    }
}

void SnapShot::save() {
    std::string str;
    *outStream << std::to_string(gameMode) << std::endl;
    str = std::to_string(X) + " " + std::to_string(Y) + "\n";
    *outStream << str;
    if(gameMode == 1) // bases
    {
        if(base1)
        {
            str = base1->getBaseInfo();
            *outStream << str << std::endl;
            do {
                str = base1->getUnitsInfo();
                *outStream << str << std::endl;
            }while(!str.empty());
        }
        if(base2)
        {
            *outStream << "." << std::endl;
            str = base2->getBaseInfo();
            *outStream << str << std::endl;
            do {
                str = base2->getUnitsInfo();
                *outStream << str << std::endl;
            }while(!str.empty());
        }
        if(base3)
        {
            *outStream << "." << std::endl;
            str = base3->getBaseInfo();
            *outStream << str << std::endl;
            do {
                str = base3->getUnitsInfo();
                *outStream << str << std::endl;
            }while(!str.empty());
        }
    } else      // titans
    {
        *outStream << unit1->getUnitInfo() << std::endl;
        *outStream << unit2->getUnitInfo() << std::endl;
    }
    adapter->save();
}

void SnapShot::load() {
    int x, y, mode, maxUnits, health, currentUnitCount;
    Specifications values;
    std::string unitName, str;
    char unitClass;
    adapter = new Adapter();
    *inStream >> mode;
    if(inStream->fail())
        throw TypeException("int");
    if(mode != 1 && mode != 2)
        throw LogicException("incorrect mode! Request is: ", mode);
    *inStream >> x >> y;
    if(inStream->fail())
        throw TypeException("int");
    if(x <= 0)
        throw LogicException("incorrect field size: ", x);
    if(y <= 0)
        throw LogicException("incorrect field size: ", y);
    Field newField(x,y, adapter, mode);

    if(mode == 1) {
        *inStream >> x >> y >> health >> maxUnits >> currentUnitCount;
        if (inStream->fail())
            throw TypeException("int");
        if (newField.getX() < x || x < 0)
            throw LogicException("incorrect base 1 coordinate x ", x);
        if (newField.getY() < y || y < 0)
            throw LogicException("incorrect base 1 coordinate y ", y);
        if (health <= 0)
            throw LogicException("incorrect base 1 health value ", health);
        if (maxUnits <= 0)
            throw LogicException("incorrect base 1 maxUnits value ", maxUnits);
        if (currentUnitCount <= 0 || currentUnitCount > maxUnits)
            throw LogicException("incorrect base 1 maxUnits value ", maxUnits);
        base1 = newField.setBase(x, y, maxUnits, 1, health);

        ///
        for(size_t i = 0; i < currentUnitCount; i++)
        {
            *inStream >> unitName >> unitClass >> x >> y >> values.health >> values.armor >> values.attack
                   >> values.attackRange;
            if(inStream->fail())
                throw TypeException("string char int int int int int int");
            if(unitClass != 'b' && unitClass != 'd' && unitClass != 'e' && unitClass != 'f' && unitClass != 'n' && unitClass != 'p')
                throw LogicException("nonexistent class", unitClass);
            if(newField.getX() < x || x < 0)
                throw LogicException("incorrect unit coordinate x", x);
            if (newField.getY() < y || y < 0)
                throw LogicException("incorrect unit coordinate y ", y);
            if (values.health <= 0)
                throw LogicException("incorrect unit health value ", values.health);
            if (values.armor <= 0)
                throw LogicException("incorrect unit armor value ", values.armor);
            if (values.attack <= 0)
                throw LogicException("incorrect unit attack value ", values.attack);
            if (values.attackRange <= 0)
                throw LogicException("incorrect unit attackRange value ", values.attackRange);
            newField.base1->createUnit(unitClass, unitName, x, y, values);
        }

        *inStream >> str;
        if(inStream->fail()) {
            throw TypeException("incorrect file state");
        }
        if(str != ".")
            throw CheckException(str);

        // base 2
        *inStream >> x >> y >> health >> maxUnits >> currentUnitCount;
        if (inStream->fail())
            throw TypeException("int");
        if (newField.getX() < x || x < 0)
            throw LogicException("incorrect base 2 coordinate x ", x);
        if (newField.getY() < y || y < 0)
            throw LogicException("incorrect base 2 coordinate y ", y);
        if (health <= 0)
            throw LogicException("incorrect base 2 health value ", health);
        if (maxUnits <= 0)
            throw LogicException("incorrect base 2 maxUnits value ", maxUnits);
        if (currentUnitCount <= 0 || currentUnitCount > maxUnits)
            throw LogicException("incorrect base 2 maxUnits value ", maxUnits);
        base2 = newField.setBase(x, y, maxUnits, 2, health);

        ///
        for(size_t i = 0; i < currentUnitCount; i++)
        {
            *inStream >> unitName >> unitClass >> x >> y >> values.health >> values.armor >> values.attack
                      >> values.attackRange;
            if(inStream->fail())
                throw TypeException("string char int int int int int int");
            if(unitClass != 'b' && unitClass != 'd' && unitClass != 'e' && unitClass != 'f' && unitClass != 'n' && unitClass != 'p')
                throw LogicException("nonexistent class", unitClass);
            if(newField.getX() < x || x < 0)
                throw LogicException("incorrect unit coordinate x", x);
            if (newField.getY() < y || y < 0)
                throw LogicException("incorrect unit coordinate y ", y);
            if (values.health <= 0)
                throw LogicException("incorrect unit health value ", values.health);
            if (values.armor <= 0)
                throw LogicException("incorrect unit armor value ", values.armor);
            if (values.attack <= 0)
                throw LogicException("incorrect unit attack value ", values.attack);
            if (values.attackRange <= 0)
                throw LogicException("incorrect unit attackRange value ", values.attackRange);
            newField.base2->createUnit(unitClass, unitName, x, y, values);
        }

        *inStream >> str;
        if(inStream->fail()) {
            throw TypeException("incorrect file state");
        }
        if(str != ".")
            throw CheckException(str);
        // base3

        *inStream >> x >> y >> health >> maxUnits >> currentUnitCount;
        if (inStream->fail())
            throw TypeException("int");
        if (newField.getX() < x || x < 0)
            throw LogicException("incorrect base 3 coordinate x ", x);
        if (newField.getY() < y || y < 0)
            throw LogicException("incorrect base 3 coordinate y ", y);
        if (health <= 0)
            throw LogicException("incorrect base 3 health value ", health);
        if (maxUnits <= 0)
            throw LogicException("incorrect base 3 maxUnits value ", maxUnits);
        if (currentUnitCount <= 0 || currentUnitCount > maxUnits)
            throw LogicException("incorrect base 3 maxUnits value ", maxUnits);
        base3 = newField.setBase(x, y, maxUnits, 3, health);

        ///
        for(size_t i = 0; i < currentUnitCount; i++)
        {
            *inStream >> unitName >> unitClass >> x >> y >> values.health >> values.armor >> values.attack
                      >> values.attackRange;
            if(inStream->fail())
                throw TypeException("string char int int int int int int");
            if(unitClass != 'b' && unitClass != 'd' && unitClass != 'e' && unitClass != 'f' && unitClass != 'n' && unitClass != 'p')
                throw LogicException("nonexistent class", unitClass);
            if(newField.getX() < x || x < 0)
                throw LogicException("incorrect unit coordinate x", x);
            if (newField.getY() < y || y < 0)
                throw LogicException("incorrect unit coordinate y ", y);
            if (values.health <= 0)
                throw LogicException("incorrect unit health value ", values.health);
            if (values.armor <= 0)
                throw LogicException("incorrect unit armor value ", values.armor);
            if (values.attack <= 0)
                throw LogicException("incorrect unit attack value ", values.attack);
            if (values.attackRange <= 0)
                throw LogicException("incorrect unit attackRange value ", values.attackRange);
            newField.base3->createUnit(unitClass, unitName, x, y, values);
        }

        *inStream >> str;
        if(!inStream->eof())
            throw CheckException("non end");


    } else
    {
        *inStream >> unitName >> unitClass >> x >> y >> values.health >> values.armor >> values.attack
                  >> values.attackRange;
        if(inStream->fail())
            throw TypeException("string char int int int int int int");
        if(unitClass != 'b' && unitClass != 'd' && unitClass != 'e' && unitClass != 'f' && unitClass != 'n' && unitClass != 'p')
            throw LogicException("nonexistent class", unitClass);
        if(newField.getX() < x || x < 0)
            throw LogicException("incorrect unit coordinate x", x);
        if (newField.getY() < y || y < 0)
            throw LogicException("incorrect unit coordinate y ", y);
        if (values.health <= 0)
            throw LogicException("incorrect unit health value ", values.health);
        if (values.armor <= 0)
            throw LogicException("incorrect unit armor value ", values.armor);
        if (values.attack <= 0)
            throw LogicException("incorrect unit attack value ", values.attack);
        if (values.attackRange <= 0)
            throw LogicException("incorrect unit attackRange value ", values.attackRange);
        Unit* unit = TitansFabric().createUnit(unitClass, unitName, x, y, values);
        unit1 = unit;
        newField.addUnit(unit, x, y, unitName);

        *inStream >> unitName >> unitClass >> x >> y >> values.health >> values.armor >> values.attack
                  >> values.attackRange;
        if(inStream->fail())
            throw TypeException("string char int int int int int int");
        if(unitClass != 'b' && unitClass != 'd' && unitClass != 'e' && unitClass != 'f' && unitClass != 'n' && unitClass != 'p')
            throw LogicException("nonexistent class", unitClass);
        if(newField.getX() < x || x < 0)
            throw LogicException("incorrect unit coordinate x", x);
        if (newField.getY() < y || y < 0)
            throw LogicException("incorrect unit coordinate y ", y);
        if (values.health <= 0)
            throw LogicException("incorrect unit health value ", values.health);
        if (values.armor <= 0)
            throw LogicException("incorrect unit armor value ", values.armor);
        if (values.attack <= 0)
            throw LogicException("incorrect unit attack value ", values.attack);
        if (values.attackRange <= 0)
            throw LogicException("incorrect unit attackRange value ", values.attackRange);
        unit = TitansFabric().createUnit(unitClass, unitName, x, y, values);
        unit2 = unit;
        newField.addUnit(unit2, x, y, unitName);

        if(!inStream->eof())
            throw CheckException("non end");
    }
    newField.print();
    *(this->field)  = newField;
    adapter->load();
}