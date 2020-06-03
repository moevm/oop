#include "tile.hpp"
#include "../exceptions/out_of_bounds_exception.hpp"

void Tile::validateChar (int x, int y) {
    if (x < 0 || y < 0 || x > 2 || y > 2) throw out_of_range("Tile char output error");
}
