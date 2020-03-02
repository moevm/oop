#ifndef CELL_H
#define CELL_H

#include <point.h>

namespace sf {
    class RenderTarget;
}


class Object;
struct Point2i;

class Cell
{
    friend class CellGrid;
    friend class Object;

public:
    enum Type{
        Open,
        Closed
    };

protected:
    Point2i coords;
    Type type;

    float iMoveModifier;
    float fDamageModifier;
    Object *obj;

public:
    virtual ~Cell(){}

    Cell(Type type, float iMoveModifier, float fDamageModifier);
    virtual void draw(sf::RenderTarget* target, const Point2i &point, int iSize) = 0;  // Probably should cast the position of cell

    float getMoveModifier() const;

    void setObject(Object* object);
    Object* getObject() const;
    Object* pullObject();
    Point2i getPoint() const;
    Type getType() const;
};


class PCell: public Cell{
private:

public:
    PCell();
    void draw(sf::RenderTarget *target, const Point2i &point, int iSize) override;
};
















#endif // CELL_H
