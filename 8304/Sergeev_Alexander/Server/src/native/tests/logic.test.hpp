#ifndef LOGIC_LOGIC_TEST_HPP
#define LOGIC_LOGIC_TEST_HPP

#include "../base/includes.hpp"
#include "../utils/timer.hpp"
#include "../game/realtime.hpp"
#include "../tilemap/square.hpp"
#include "../components/component_storage.hpp"
#include "../generators/simple.hpp"
#include "../generators/perlin.hpp"

namespace unit_testing {
    void test_logic () {
        std::cout << "* test_logic [started]" << std::endl; //TODO logger

        stts::vector2<int> size {35, 35};
        std::set<int> players;
        players.emplace(1);
        players.emplace(2);
        generators::simple gen(1, players, size);
        //generators::perlin gen(1, 3, 0.5, players, size);
        std::unique_ptr<game::abstract_game> game = gen.generate();

        // saving
        //json k;
        //game.serialize(k);
        //std::cout << k.dump(2);

        // json sig;
        // sig[com_move_type]["type"] = "move";
        // vector2<int> target_position = vector2<int>(1, 2);
        // target_position.serialize(sig[com_move_type]["position"]);
        // json out;
        // game.signal(sig, out);


        //timer t = timer();
        //t.setInterval(game.update, 1000);

        std::cout << "* Print 'q' to stop testing\n"
                     "* Enter empty string to update" << std::endl;
        std::string command = "";
        while (true) {
            std::getline(std::cin, command);

            if (command.empty()) {
                json j;
                game->update(j);
            }
            else if (command == "p") {
                json j;
                game->serialize_concrete_player(2, j);
                std::cout << j.dump(2) << std::endl;
            }
            else if (command == "q") {
                break;
            }
            else {
                json input2;
                input2[com::j_move_signal::is_moving] = true;
                stts::vector2<int> position = stts::vector2<int>(rand() % game->get_tilemap().get_scale().x, rand() % game->get_tilemap().get_scale().y);
                position.serialize(input2[com::j_move_signal::move_target]);
                input2[com::j_attack_signal::attack_target] = 4;
                input2[com::j_attack_signal::is_attacking] = true;
                json output;
                game->get_unit(2)->signal(*(game.get()), com::j_move::type, input2);
                game->get_unit(2)->signal(*(game.get()), com::j_attack::type, input2);

                json input1;
                input1[com::j_spawner_signal::production_line] = 3;
                output = {};
                game->get_unit(1)->signal(*(game.get()), com::j_spawner::type, input1);
                //game->signal(input, output);
            }
            nlohmann::json_tools::print_tilemap(game->get_tilemap());
        }
        std::cout << "* test_logic [success]" << std::endl;
    }
}

#endif //LOGIC_LOGIC_TEST_HPP
