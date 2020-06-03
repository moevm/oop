#ifndef GOGOLEV_STRATEGY_TILE_HPP
#define GOGOLEV_STRATEGY_TILE_HPP

#include "../stl.hpp"
#include "../enums.hpp"

class Tile {
public:
    void validateChar(int x, int y);
    virtual char getId() = 0;
    virtual char getChar (int x, int y) = 0;
    virtual bool allow (DamageType damageType) = 0;
    virtual bool allow (MovingType movingType) = 0;
};


#endif //GOGOLEV_STRATEGY_TILE_HPP
