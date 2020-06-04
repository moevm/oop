#ifndef LOGIC_TILEMAP_PERLIN_BUILDER_HPP
#define LOGIC_TILEMAP_PERLIN_BUILDER_HPP

#include "map_builder.hpp"
#include "vector2.hpp"

class map_perlin_builder : public map_builder {
protected:
    int seed;
public:
    explicit map_perlin_builder (int nseed, const stts::vector2<int>& nscale);
    map_builder& generate_ground () override; //TODO arguments
    map_builder& generate_units () override;

    enum seeds { small, medium, large };
};

map_perlin_builder::map_perlin_builder (int nseed, const stts::vector2<int>& nscale) : seed(nseed) {
    scale = nscale;
    //TODO
}

map_builder& map_perlin_builder::generate_ground () {
    //TODO
    return *this;
}

map_builder& map_perlin_builder::generate_units () {
    //TODO
    return *this;
}


#endif //LOGIC_TILEMAP_PERLIN_BUILDER_HPP
