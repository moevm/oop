#ifndef LOGIC_STEPPED_HPP
#define LOGIC_STEPPED_HPP

#include "abstract_game.hpp"

namespace game {
    // JSON
    namespace j_stepped {
        const std::string type = TOSTRING(stepped);
    }

    class stepped : public game::abstract_game {
    public:
        explicit stepped();
        explicit stepped(json& package);
        const std::string& type () const override;
        void serialize_concrete_player (int player_uid, json& package) override;
        void update (json& output) override;
    };
}


#endif //LOGIC_STEPPED_HPP
