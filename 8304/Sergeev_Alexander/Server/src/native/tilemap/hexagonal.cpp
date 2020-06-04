#include "hexagonal.hpp"

tilemap::hexagonal::hexagonal (const stts::vector2<int>& nscale) : abstract_tilemap(nscale) {
    // TODO
}

tilemap::hexagonal::hexagonal (json& package) {
    hexagonal::deserialize(package);
}

const std::string& tilemap::hexagonal::type () const {
    return j_hexagonal::type;
}

tile::base_tile& tilemap::hexagonal::get_tile (int x, int y) {
    return *data[0];
}

void tilemap::hexagonal::set_tile (int x, int y, tile::base_tile* item) {

}

bool tilemap::hexagonal::is_valid (int x, int y) const {
    return false;
}

std::vector<stts::vector2<int>> tilemap::hexagonal::get_neighbours (int x, int y) {
    return std::vector<stts::vector2<int>>();
}

float tilemap::hexagonal::get_distance (int source_x, int source_y, int destination_x, int destination_y) {
    return 0;
}

std::list<stts::vector2<int>> tilemap::hexagonal::get_path (int source_x, int source_y, int destination_x, int destination_y) {
    return std::list<stts::vector2<int>>();
}



