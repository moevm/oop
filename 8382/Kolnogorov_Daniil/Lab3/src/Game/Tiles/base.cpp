#include "base.hpp"
#include "../Units/units.hpp"
#include <cstdio>
#include <string>

Base::Base(unsigned owner_id, Coordinates coors) {
    this->coors = coors;
    this->owner_id = owner_id;
    this->health_max = BASE_HEALTH_MAX;
    this->health = this->health_max;
    this->can_walk = false;
    this->can_build = false;
    this->type = TILE_BASE;
    this->max_dist = BASE_MAX_DISTANCE;
    this->neutral = nullptr;
}

TileInterface* Base::create_copy() {
    return new Base(owner_id, coors);
}

string Base::get_info() {
    string info;

    info += "BASE\n";
    info += "Owner: " + to_string(owner_id) + "\n";
    info += "Health: " + to_string(health) + "/" + to_string(health_max);

    return info;
}
