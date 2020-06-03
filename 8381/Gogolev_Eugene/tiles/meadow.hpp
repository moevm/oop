#ifndef GOGOLEV_STRATEGY_MEADOW_HPP
#define GOGOLEV_STRATEGY_MEADOW_HPP

#include "tile.hpp"

class Meadow : public Tile {
public:
    const static char id = 'M';
    char getId() override ;
    char getChar(int x, int y) override;
    bool allow(DamageType damageType) override;
    bool allow(MovingType movingType) override;
};


#endif //GOGOLEV_STRATEGY_MEADOW_HPP
