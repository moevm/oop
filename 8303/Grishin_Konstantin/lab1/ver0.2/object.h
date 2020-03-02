#ifndef OBJECT_H
#define OBJECT_H

#include "point.h"


namespace sf {
    class RenderTarget;
}

class Cell;
class CellGrid;

class Object
{
    friend class Cell;

public:
    enum Team{
        Red,
        Blu,
        Neutral
    };

    enum Type{
        Unit
    };

protected:
    void setActive(bool act);
    void setPosition(Cell *cell);      // relocate object
    void setTeam(Team team);

private:
    Team team = Neutral;
    const Object::Type objType;
    Cell *cell = nullptr;
    bool bActive;

public:
    virtual ~Object(){}
    Object(Cell *cell, Object::Type objType);
    Object(const Object &object) = delete;
    Object(Object&&) = delete;
    virtual Object* copy(CellGrid* grid) const = 0;

    Object::Type getObjectType() const;

    virtual void draw(sf::RenderTarget *target, int rect_size) = 0;
    virtual void move(Cell* dest) = 0;    // move with animation;

    Point2i getPos() const;
    Cell* getCell() const;
    Team getTeam() const;
    bool isActive() const;
};

#endif // OBJECT_H
