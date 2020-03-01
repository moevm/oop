//
// Created by shenk on 01.03.2020.
//

#ifndef UNTITLED13_GAMEOBJECT_H
#define UNTITLED13_GAMEOBJECT_H

#include "../Point.h"

enum class ObjectType{

    UNIT,
    BASE,
    NEUTRAL_OBJECT,
    UNKNOWN

};

class GameObject {

    friend class GameField;

protected:

    ObjectType type;
    Point position;
    bool isOnField = false;

public:

    GameObject(ObjectType type): type(type){}
    Point getPosition() { return position; }
    ObjectType getType() { return type; }

};


#endif //UNTITLED13_GAMEOBJECT_H
