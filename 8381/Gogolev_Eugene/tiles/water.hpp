#ifndef GOGOLEV_STRATEGY_WATER_HPP
#define GOGOLEV_STRATEGY_WATER_HPP

#include "tile.hpp"

class Water : public Tile {
public:
    const static char id = 'W';
    char getId() override ;
    char getChar(int x, int y) override;
    bool allow(DamageType damageType) override;
    bool allow(MovingType movingType) override;
};


#endif //GOGOLEV_STRATEGY_WATER_HPP
