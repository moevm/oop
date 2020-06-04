#ifndef LOGIC_TILEMAP_SQUARE_TEST_HPP
#define LOGIC_TILEMAP_SQUARE_TEST_HPP

#include "../../base/includes.hpp"
#include "../../tilemap/square.hpp"


namespace unit_testing {
    void test_tilemap_square() {
        std::cout << "* test_tilemap_square [started]" << std::endl;
        json j;
        //
        tilemap::abstract_tilemap* t_square = new tilemap::square(stts::vector2<int>(1, 2));
        t_square->serialize(j);
        std::cout << j.dump(2) << std::endl;
        delete t_square;
        //
        t_square = new tilemap::square(stts::vector2<int>(3, 4));
        j = {};
        t_square->serialize(j);
        std::cout << j.dump(2) << std::endl;
        //
        t_square->set_tile(stts::vector2<int>(1, 2), new tile::damage_dealer(0.5f, 2));
        t_square->set_tile(stts::vector2<int>(2, 2), new tile::money_dealer(0.5f, 20));
        j = {};
        t_square->serialize(j);
        std::cout << j.dump(2) << std::endl;
        //
        delete t_square;
        t_square = new tilemap::square(j);
        j = {};
        t_square->serialize(j);
        std::cout << j.dump(2) << std::endl;

        //t_square->deserialize() TODO

        std::cout << "* test_tilemap_square [success]" << std::endl;
    }
}

#endif //LOGIC_TILEMAP_SQUARE_TEST_HPP
