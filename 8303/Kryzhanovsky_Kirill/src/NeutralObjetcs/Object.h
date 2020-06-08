//
// Created by therealyou on 11.03.2020.
//

#ifndef LAB1_OBJECT_H
#define LAB1_OBJECT_H

#include "ObjectsType.h"
#include "../Units/Unit.h"

class Object {
protected:
    int x, y ,buffValue;
    ObjectsType type;
    void addHealth(Unit *unit);
    void addDamage(Unit *unit);
    void addArmor(Unit *unit);
    void addPoison(Unit *unit);
public:
    Object(int x, int y, int buffValue, ObjectsType type);
    void getBuff(Unit *unit);
    virtual char getChar() = 0;

    Object& operator>>(Unit *unit);
};


#endif //LAB1_OBJECT_H
