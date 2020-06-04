#ifndef LOGIC_TILE_DAMAGE_DEALER_TEST_HPP
#define LOGIC_TILE_DAMAGE_DEALER_TEST_HPP

#include "../../base/includes.hpp"

namespace unit_testing {
    void test_damage_dealer() {
        std::cout << "* test_tile_damage [started] (depends on unit)" << std::endl;

        const int height = 100;
        const int damage = 200;
        tile::damage_dealer td = tile::damage_dealer(height, damage);
        assert(td.type() == tile::j_damage_dealer::type);
        assert(td.get_height() == height);
        assert(td.is_occupied() == false);
        //unit_prototype proto_1 = unit_prototype("test_proto_1");
        //proto_1.;
        //unit unit_1 = unit();
        //unit_1.set_parameter("")

        std::cout << "* test_tile_damage [success]" << std::endl;
    }
}

#endif //LOGIC_TILE_DAMAGE_DEALER_TEST_HPP
