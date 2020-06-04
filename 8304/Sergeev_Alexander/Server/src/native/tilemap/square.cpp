#include "square.hpp"
#include "../_temp/pathfinder.hpp"

tilemap::square::square (const stts::vector2<int>& nscale) : abstract_tilemap(nscale) { }

tilemap::square::square (json& package) {
    square::deserialize(package);
}

const std::string& tilemap::square::type () const {
    return j_square::type;
}

tile::base_tile& tilemap::square::get_tile (int x, int y) {
    if (!is_valid(x, y)) throw out_of_bounds_exception("Tile out of tilemap borders");
    return *data[y * scale.x + x];
}

void tilemap::square::set_tile (int x, int y, tile::base_tile* item) {
    if (!is_valid(x, y)) throw out_of_bounds_exception("Tile out of tilemap borders");
    delete data[y * scale.x + x];
    data[y * scale.x + x] = item;
}

bool tilemap::square::is_valid (int x, int y) const {
    return !(x < 0 || x >= scale.x || y < 0 || y >= scale.y);
}

std::vector<stts::vector2<int>> tilemap::square::get_neighbours (int x, int y) {
    std::vector<stts::vector2<int>> result = std::vector<stts::vector2<int>>(); // TODO maybe references
    if (is_valid(x + 1, y)) result.emplace_back(x + 1, y);
    if (is_valid(x - 1, y)) result.emplace_back(x - 1, y);
    if (is_valid(x, y + 1)) result.emplace_back(x, y + 1);
    if (is_valid(x, y - 1)) result.emplace_back(x, y - 1);
    return result;
}

float tilemap::square::get_distance (int source_x, int source_y, int destination_x, int destination_y) {
    int a = destination_x - source_x;
    int b = destination_y - source_y;
    return sqrtf((float)(a * a + b * b)); // TODO optimize
}

std::list<stts::vector2<int>> tilemap::square::get_path (int source_x, int source_y, int destination_x, int destination_y) {
    std::list<stts::vector2<int>> path = std::list<stts::vector2<int>>();
    if (!is_valid(source_x, source_y) || !is_valid(destination_x, destination_y)) return path;
    // TODO
    /*while (source_x != destination_x && source_y != destination_y) {
        if (source_x > destination_x) source_x--;
        else if (source_x < destination_x) source_x++;
        if (source_y > destination_y) source_y--;
        else if (source_y < destination_y) source_y++;
        path.emplace_back(source_x, source_y);
    }*/
    pathfinder pth(*this);
    path = pth.find_path(stts::vector2<int>(source_x, source_y), stts::vector2<int>(destination_x, destination_y));
    path.pop_back();
    return path;
}





