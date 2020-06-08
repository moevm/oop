#ifndef OBJECT_H
#define OBJECT_H

#include "game_elements/entity.h"

class Object : public Entity
{
protected:
public:
    enum Type{
        Usable,
        NonUsable
    };

    void update(float) override{}

    virtual ~Object(){};
    virtual Object* destroy() = 0;
    virtual Object* treat() = 0;

    virtual void setDurability(int dura) = 0;
    virtual int getDurability() const = 0;
    virtual int getScore() const = 0;

    virtual Type getObjectType() const = 0;

    Entity::Type getEntityType() const override
    { return Entity::Object; }

    Team getTeam() const override
    { return Team::Neutral; }

};

#endif // OBJECT_H
