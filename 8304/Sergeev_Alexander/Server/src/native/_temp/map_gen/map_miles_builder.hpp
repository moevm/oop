#ifndef LOGIC_TILEMAP_BOX_BUILDER_HPP
#define LOGIC_TILEMAP_BOX_BUILDER_HPP

#include "map_builder.hpp"

// TODO add generating pivot point for every players
class map_miles_builder : public map_builder {
protected:
    int seed;
public:
    explicit map_miles_builder (int nseed = 0);
    map_builder& generate_ground () override; //TODO arguments
    map_builder& generate_units () override;

    enum seeds { small, medium, large };
};

map_miles_builder::map_miles_builder (int nseed) : seed(nseed) {
    if (seed > 999) {
        scale.x = seed / 1000;
        scale.y = seed % 1000;
        if (scale.x % 2 != 0) scale.x -= 1;
        if (scale.y % 2 != 0) scale.y -= 1;
        if (scale.x < 10) scale.x = 10;
        if (scale.y < 10) scale.y = 10;
        if (scale.x > 250) scale.x = 250;
        if (scale.y > 250) scale.y = 250;
    }
    else {
        switch (seed) {
            case seeds::small:
                scale.x = scale.y = 50;
                break;
            case seeds::medium:
                scale.x = scale.y = 100;
                break;
            case seeds::large:
                scale.x = scale.y = 150;
                break;
            default:
                scale.x = scale.y = 100;
                break;
        }
    }
}

map_builder& map_miles_builder::generate_ground () {
    //result = std::make_shared<abstract_tilemap>(scale);

    //Test generation
    //vector2<int> i = vector2<int>(0, 0); //TODO Change to iterator (L1)
    // for (int i = 0; i < scale.y; ++i) {
    //     for (int k = 0; k < scale.x; ++k) {
    //         // TODO maybe add tile.set_texture etc.
    //         if (i == k) result->get_tile(vector2<int>(i, k)) = tile(true, 1, tile::T_Ground);
    //     }
    // }
    //

    //logger::get().log(logger::O_Cons | logger::T_Info, "Game field initialized with ", scale.x, " width and ", scale.y, " height");
    return *this;
}

map_builder& map_miles_builder::generate_units () {
    //TODO
    //TODO don't use game singleton to make units. Do something else...
    return *this;
}

#endif //LOGIC_TILEMAP_BOX_BUILDER_HPP
