#ifndef LOGIC_PLAYER_TEST_HPP
#define LOGIC_PLAYER_TEST_HPP

#include "../../base/includes.hpp"
#include "../../structs/player.hpp"

namespace unit_testing {
    void test_player() {
        logger::say(l::debug) << "Player testing started..." << logger::out;
        logger::say() << "Creating a player from team 42" << logger::out;
        stts::player player(42);
        json j;
        player.serialize(j);
        logger::say()  << "Serialized: " << j << logger::out;
        logger::say() << "Creating from JSON (via copying operator)" << logger::out;
        stts::player nplayer = stts::player(j);
        logger::say(l::debug) << "Success!" << logger::out;
        logger::say(l::debug) << "Player testing finished!" << logger::out;
        logger::say() << logger::over;
    }
}

#endif //LOGIC_PLAYER_TEST_HPP