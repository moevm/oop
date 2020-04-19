#pragma once

#include <vector>

#include "../Units/units.hpp"
#include "tiles.hpp"

#define BASE_MAX_DISTANCE 3
#define BASE_HEALTH_MAX   200

using namespace std;

class Base : public Tile {
public:
    unsigned owner_id;
    unsigned health_max;
    unsigned health;

    Base(unsigned owner_id, Coordinates coors);
    TileInterface* create_copy();

    void damage(unsigned damage) {
        if (health > damage) {
            health -= damage;
        } else {
            health = 0;
        }
    }

    string get_info();
};
