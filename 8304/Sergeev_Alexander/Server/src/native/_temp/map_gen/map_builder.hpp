#ifndef LOGIC_TILEMAP_GENERATOR_H
#define LOGIC_TILEMAP_GENERATOR_H

#include "../../base/includes.hpp"
#include "../../tilemap/abstract_tilemap.hpp"
#include "vector2.hpp"
#include "abstract_tilemap.hpp"

//TODO Moved separated cuz this is frequently changing zone
//TODO Made builder https://refactoring.guru/design-patterns/builder
//TODO Made abstract
class map_builder {
protected:
    stts::vector2<int> scale;
    std::shared_ptr<tilemap::abstract_tilemap> result;

public:
    explicit map_builder (const stts::vector2<int>& nscale = stts::vector2<int>(8, 8));
    virtual map_builder& generate_ground (); //TODO arguments
    virtual map_builder& generate_units ();
    std::shared_ptr<tilemap::abstract_tilemap> get_result ();
    virtual ~map_builder ();
};

map_builder::map_builder (const stts::vector2<int>& nscale) : scale(nscale) { }

map_builder& map_builder::generate_ground () {
    //result = std::make_shared<abstract_tilemap>(scale);
    return *this;
}
map_builder& map_builder::generate_units () {
    //unit u = unit("");
    //TODO how to return?
    return *this;
}
std::shared_ptr<tilemap::abstract_tilemap> map_builder::get_result () {
    return result;
}
map_builder::~map_builder () {
    result = nullptr;
}


#endif //LOGIC_TILEMAP_GENERATOR_H