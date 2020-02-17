#ifndef CELL_H
#define CELL_H

#include "point.h"

namespace sf {
    class RenderTarget;
}

class Cell{
private:
    enum Type{
        wall,
        open
    };

    Type type = open;

public:
    virtual ~Cell(){}

    Cell(Cell::Type type);
    Cell();

    virtual void draw(sf::RenderTarget* target, Point position, int size);

    Cell::Type getType() const;
};


#endif // CELL_H
