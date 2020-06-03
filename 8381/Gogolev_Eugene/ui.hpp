#ifndef GOGOLEV_STRATEGY_UI_HPP
#define GOGOLEV_STRATEGY_UI_HPP

#include "stl.hpp"

class Tile;
class Unit;

class UI {
public:
    // TODO init to ctor

    void init(int x, int y);

    void displayTile(int x, int y, Tile *tile);

    void displayUnit(Unit *unit);

    void displayPixel(int x, int y, char p);

    void clear();

    void showFrame();

private:
    int sizeX;
    int sizeY;
    char* frame = nullptr;

    int toIndex(int x, int y, int charX, int charY) const;
};



#endif //GOGOLEV_STRATEGY_UI_HPP
