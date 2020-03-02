#ifndef UNIT_H
#define UNIT_H

#include "object.h"

struct Point2i;
class Cell;

class Unit : public Object
{
public:
    enum Type{
        Combat,
        Peace
    };

private:
    const Type unitType;

public:
    virtual ~Unit(){}
    Unit(Cell *cell, Unit::Type unitType);
    Unit::Type getUnitType() const;

    virtual void draw(sf::RenderTarget *target, int rect_size) = 0;
    virtual void move(Cell *dest) = 0;    // move with animation;

    virtual void damage(float dmg) = 0;   // probably should cast shell
                                        // instead int to differently
                                        // modificate damage

    virtual void heal(float iAddHealth) = 0;

    virtual float health() const = 0;
    virtual float maxHealth() const = 0;
    virtual float steps() const = 0;
    virtual float maxSteps() const = 0;
    virtual void updateSteps() = 0;
};

#endif // UNIT_H
