#ifndef GOGOLEV_STRATEGY_FORTRESS_HPP
#define GOGOLEV_STRATEGY_FORTRESS_HPP

#include "tile.hpp"

class Fortress : public Tile {
public:
    const static char id = 'F';
    char getId() override ;
    char getChar(int x, int y) override;
    bool allow(DamageType damageType) override;
    bool allow(MovingType movingType) override;
};

#endif //GOGOLEV_STRATEGY_FORTRESS_HPP
