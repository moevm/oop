//
// Created by therealyou on 11.03.2020.
//

#include "Object.h"

Object::Object(int x, int y, int buffValue, ObjectsType type) :
x(x), y(x), buffValue(buffValue), type(type)
{
}

void Object::getBuff(Unit *unit) {
    if (buffValue == 0){
        return;
    }
    switch (type){
        case ObjectsType::WEAPON:
            addDamage(unit);
            break;
        case ObjectsType::POISON:
            addPoison(unit);
            break;
        case ObjectsType::ARMOR:
            addArmor(unit);
            break;
        case ObjectsType::MEDICINE:
            addHealth(unit);
            break;
    }
}

void Object::addHealth(Unit *unit) {
    int k = buffValue;
    switch (unit->type){
        case UnitsType::ELF:
            k += 15;
            break;
        case UnitsType::WITCH:
            k += 16;
            break;
        case UnitsType::PEON:
            k += 13;
            break;
        case UnitsType::SHOOTER:
            k += 14;
            break;
        case UnitsType::TROLL:
            k += 15;
            break;
        case UnitsType::GOBLIN:
            k += 16;
            break;
    }
    unit->setHealth(unit->getHealth() + k);
}

void Object::addDamage(Unit *unit) {
    int k = buffValue;
    switch (unit->type){
        case UnitsType::ELF:
            k += 15;
            break;
        case UnitsType::WITCH:
            k += 16;
            break;
        case UnitsType::PEON:
            k += 13;
            break;
        case UnitsType::SHOOTER:
            k += 14;
            break;
        case UnitsType::TROLL:
            k += 15;
            break;
        case UnitsType::GOBLIN:
            k += 16;
            break;
    }
    unit->setDamage(unit->getDamage() + k);
}

void Object::addArmor(Unit *unit) {
    int k = buffValue;
    switch (unit->type){
        case UnitsType::ELF:
            k += 15;
            break;
        case UnitsType::WITCH:
            k += 16;
            break;
        case UnitsType::PEON:
            k += 13;
            break;
        case UnitsType::SHOOTER:
            k += 14;
            break;
        case UnitsType::TROLL:
            k += 15;
            break;
        case UnitsType::GOBLIN:
            k += 16;
            break;
    }
    unit->setArmor(unit->getArmor() + k);
}

void Object::addPoison(Unit *unit) {
    int k = buffValue;
    switch (unit->type){
        case UnitsType::ELF:
            k += 15;
            break;
        case UnitsType::WITCH:
            k += 16;
            break;
        case UnitsType::PEON:
            k += 13;
            break;
        case UnitsType::SHOOTER:
            k += 14;
            break;
        case UnitsType::TROLL:
            k += 15;
            break;
        case UnitsType::GOBLIN:
            k += 16;
            break;
    }
    unit->setHealth(unit->getHealth() - k);
}

Object &Object::operator>>(Unit *unit) {
    if (x == unit->getX() && y == unit->getY()) {
        getBuff(unit);
        buffValue = 0;
    } else {
        std::cout << "Unit is not in the same place like this neutral object" << std::endl;
    }
    return *this;
}

//
//void operator>>(Object *object, Unit *unit) {
//    if (object->x == unit->getX() && object->y == unit->getY()){
//        object->getBuff(unit);
//    } else {
//        std::cout << "Unit is not in the same place like this neutral object" << std::endl;
//    }
//}