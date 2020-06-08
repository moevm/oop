#ifndef BUILDING_H
#define BUILDING_H

#include "game_elements/entity.h"
#include "game_elements/units/unit.h"

class Building : public Entity
{
public:
    enum Rot{
        Up,
        Right,
        Down,
        Left
    };

    enum Type{
        Base,
        Tower,
        Barrack
    };

    virtual void damage(float dmg) = 0;
    virtual void setHealth(float hp) = 0;

    virtual float getHealth() const = 0;
    virtual float getMaxHealth() const = 0;
    virtual Building::Rot getRotation() const = 0;   // face of the building

    virtual class Unit* createUnit(Unit::Type type) = 0;

    virtual Building::Type getBuildingType() const = 0;
    Entity::Type getEntityType() const {return Entity::Building; }
};

#endif // BUILDING_H
