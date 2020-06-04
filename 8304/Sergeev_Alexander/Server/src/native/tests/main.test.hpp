#ifndef LOGIC_MAIN_TEST_HPP
#define LOGIC_MAIN_TEST_HPP

#include "logic.test.hpp"
#include "lr1.test.hpp"
#include "lr2.test.hpp"
#include "lr3.test.hpp"
#include "lr4.test.hpp"
#include "lr5.test.hpp"
#include "lr6.test.hpp"
#include "lr7.test.hpp"

#include "components/com_attack.test.hpp"
#include "components/com_mortal.test.hpp"
#include "components/com_move.test.hpp"
#include "components/com_storage.test.hpp"

#include "entities/unit.test.hpp"
#include "entities/unit_factory.test.hpp"
#include "entities/unit_prototype.test.hpp"

#include "game/base_game.test.hpp"
#include "game/game_realtime.test.hpp"
#include "game/game_stepped.test.hpp"

//#include "game_states/" TODO

#include "lobby/game_lobby.test.hpp"
#include "lobby/game_session.test.hpp"

#include "logger/logger.test.hpp"
#include "filesys/file_gate.test.hpp"

#include "structs/chat_message.test.hpp"
#include "structs/broadcast_message.test.hpp"
#include "structs/parameter_map.test.hpp"
#include "structs/player.test.hpp"
#include "structs/vector2.test.hpp"

#include "tilemap/tilemap_hexagonal.test.hpp"
#include "tilemap/tilemap_square.test.hpp"

#include "tiles/tile.test.hpp"
#include "tiles/tile_damage_dealer.test.hpp"
#include "tiles/tile_money_dealer.test.hpp"


namespace unit_testing {
    void unit_test_all () {
        std::cout << "***STARTING UNIT TESTING***" << std::endl;
        test_logger();
        test_file_gate();
        logger::say(l::debug) << "Testing structures..." << logger::out;
        test_chat_message();
        test_broadcast_message();
        test_parameter_map();
        test_player();
        test_vector2();
        std::cout << "***UNIT TESTING SUCCESS***" << std::endl;
    }

    void integration_test_all () {
        std::cout << "***STARTING INTEGRATION TESTING***" << std::endl;
        test_lr1();
        test_lr2();
        test_lr3();
        test_lr4();
        test_lr5();
        test_lr6();
        test_lr7();
        std::cout << "***INTEGRATION TESTING SUCCESS***" << std::endl;
    }

    void test_cli () {
        std::cout << "* testing [started] \n"
                     "* Print 'u' to unit testing\n"
                     "* Print 'i' to integration testing\n"
                     "* Print 'l' to test logic\n"
                     "* Print '1'-'7' to test specific lab\n"
                     "* Print 'q' to quit\n" << std::endl; //TODO logger

        std::string command = "";
        while (command != "q") {
            //std::cin >> command;
            std::getline(std::cin, command);
            switch (command[0]) {
                case 'q':
                    break;
                case 'u':
                    unit_test_all();
                    break;
                case 'i':
                    integration_test_all();
                    break;
                case 'l':
                    test_logic();
                    break;
                case '1':
                    test_lr1();
                    break;
                case '2':
                    test_lr2();
                    break;
                case '3':
                    test_lr3();
                    break;
                case '4':
                    test_lr4();
                    break;
                case '5':
                    test_lr5();
                    break;
                case '6':
                    test_lr6();
                    break;
                case '7':
                    test_lr7();
                    break;
                default:
                    break;
            }
        }
        std::cout << "* testing [success]" << std::endl;
    }
}

#endif //LOGIC_MAIN_TEST_HPP
