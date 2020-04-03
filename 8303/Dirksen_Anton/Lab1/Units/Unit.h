//
// Created by mensch on 02.03.2020.
//

#ifndef OOP_LABS_UNIT_H
#define OOP_LABS_UNIT_H


#include "../Point.h"
#include "../Object.h"
#include "../Field/Field.h"


class Unit : public Object{

public:
    Unit() {};
    void move(Point point);
    ObjectType type() const override;

protected:
    int health;
    int damage;
};


#endif //OOP_LABS_UNIT_H
