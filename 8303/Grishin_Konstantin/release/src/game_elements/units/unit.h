#ifndef UNIT_H
#define UNIT_H

#include "game_elements/entity.h"
#include "game_elements/units/unit_action.h"

class Unit : public Entity
{
public:
    struct wrong_team : public std::exception{
        const char * what() const throw()
        {
            return "unit can't be neutral";
        }
    };

    enum Type{
        Melee,
        Range,
        Nuker,
        Worker
    };
    
    virtual void move(int x, int y) = 0;    // relocates unit with state changing
    virtual sf::Vector2f getMovingOffset() const = 0;
    virtual bool isMovable() const = 0;

    virtual void setHealth(float hp) = 0;
    virtual void setSteps(float steps) = 0;
    virtual void setExtra(float extra) = 0;

    virtual void damage(float dmg, const std::string& id) = 0;
    virtual void heal(float hp) = 0;
    virtual void increase(float val) = 0;
    virtual void resetSteps() = 0;
    
    UnitAction action() const;
    virtual void setActionState() = 0;

    virtual float getHealth() const = 0;
    virtual float getMaxHealth() const = 0;
    
    virtual float getMaxSteps() const = 0;
    virtual float getSteps() const = 0;

    virtual float getExtra() const = 0;
    
    virtual Type getUnitType() const = 0;
    Entity::Type getEntityType() const {return Entity::Unit;}

protected:
    virtual void constructAction(UnitAction& action) const = 0;
};

#endif // UNIT_H
