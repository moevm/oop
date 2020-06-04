#ifndef LOGIC_TILE_MONEY_DEALER_TEST_HPP
#define LOGIC_TILE_MONEY_DEALER_TEST_HPP

#include "../../base/includes.hpp"

namespace unit_testing {
    void test_money_dealer() {
        std::cout << "* test_tile_money [started]" << std::endl;

        const int height = 100;
        const int money = 300;

        tile::money_dealer tm = tile::money_dealer(height, money);
        assert(tm.type() == tile::j_money_dealer::type);
        assert(tm.get_height() == height);
        assert(tm.is_occupied() == false);
        //unit_prototype proto_2 = unit_prototype("test_proto_1");
        //unit unit_2;

        std::cout << "* test_tile_money [success]" << std::endl;
    }
}

#endif //LOGIC_TILE_MONEY_DEALER_TEST_HPP
