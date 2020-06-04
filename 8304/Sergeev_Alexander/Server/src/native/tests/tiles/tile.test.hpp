#ifndef LOGIC_TILE_TEST_HPP
#define LOGIC_TILE_TEST_HPP

#include "../../base/includes.hpp"
#include "../../tiles/base_tile.hpp"

#include "../../tiles/money_dealer.hpp"
#include "../../entities/unit.hpp"

namespace unit_testing {
    void test_tile() {
        std::cout << "* test_tile [started] (depends on unit, unit_prototype)" << std::endl;

        const int height = 100;

        tile::base_tile t = tile::base_tile(height);
        assert(t.type() == tile::j_base_tile::type);
        assert(t.get_height() == height);
        assert(t.is_occupied() == false);

        std::cout << "* test_tile [success]" << std::endl;
    }
}


#endif //LOGIC_TILE_TEST_HPP
