//
// Created by Глебушунок on 15.03.2020.
//

#ifndef OOP_LAB1_GAMEOBJECT_H
#define OOP_LAB1_GAMEOBJECT_H

#include <ostream>
#include "Point.h"

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

    virtual void print(std::ostream &stream) const = 0;

public:

    explicit GameObject(ObjectType type): type(type){}
    Point getPosition() { return position; }
    ObjectType getType() { return type; }

    friend std::ostream &operator<<(std::ostream &stream, const GameObject &object);

};

#endif //OOP_LAB1_GAMEOBJECT_H
