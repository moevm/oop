#ifndef BATTLEFORHONOUR_GAMEOBJECT_H
#define BATTLEFORHONOUR_GAMEOBJECT_H


#include <ostream>
#include "../GameField/Point.h"
#include "../Logs/Log.h"
#include "ObjectType.h"


class GameObject {

    friend class GameField;

protected:

    ObjectType type;
    Point pos;
    bool isOnField = false;

    virtual void print(std::ostream &stream) const = 0;

public:

    explicit GameObject(ObjectType type): type(type){}
    Point getPosition() {
        return pos;
    }
    ObjectType getType() {
        return type;
    }

    friend std::ostream &operator<<(std::ostream &stream, const GameObject &object);
    friend LogProxy& operator<<(LogProxy &logger, GameObject &object){

        logger << "Object = x: " << object.pos.x << " y: " << object.pos.y;
        return logger;

    }

};


#endif //BATTLEFORHONOUR_GAMEOBJECT_H
