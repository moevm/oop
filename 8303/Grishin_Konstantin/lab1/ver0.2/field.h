#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <string>

#include "object.h"

#define PIXELS 0
#define CELLS 1

namespace sf {
    class RenderTarget;
}

class CellGrid;
class Cell;
class ObjectContainer;
class Unit;
class BluCombatFactory;
class RedCombatFactory;
struct Point2i;


class Field
{
public:
    static const int cell_size = 64;

private:
    const unsigned int iWidth;
    const unsigned int iHeight;
    const unsigned int iMaxUnits;

    CellGrid *grid;
    int iTurns = 0;

    BluCombatFactory *bluCF;
    RedCombatFactory *redCF;

    ObjectContainer *objects;
    ObjectContainer *bluObjects;
    ObjectContainer *redObjects;

    Unit *markedUnit = nullptr;
    std::vector<Cell*> possibleWays;

    void calculatePossibleWays();

public:
    ~Field();
    Field(unsigned int iWidth, unsigned int iHeight);
    Field(const Field &field);
    Field(Field&&);

    Point2i getSize() const;
    Point2i getPointFromPixels(sf::RenderTarget *target, int x_pix, int y_pix);

    void createUnit(const std::string &id, int x, int y, bool bPosType = 0);
    void deleteUnit(int x, int y, bool bPosType = 0);

    void draw(sf::RenderTarget *target);
    void lightSpotedUnit(sf::RenderTarget *target);
    void lightPossibleWays(sf::RenderTarget *target);

    void spotCell(sf::RenderTarget *target, int x, int y, bool bPosType = 0);  // (x.y) - window coordinates
    void spotUnit(Object::Team team, int x, int y, bool bPosType = 0);
    void clearSelection();
    void moveSpottedUnit(int x, int y, bool bPosType);

    void addObject(Object *add, Point2i pos);
    void refresh();
    int turnsPassed() const;
};

#endif // FIELD_H
