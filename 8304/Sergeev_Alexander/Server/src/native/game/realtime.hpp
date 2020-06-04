#ifndef LOGIC_REALTIME_HPP
#define LOGIC_REALTIME_HPP

#include "abstract_game.hpp"

namespace game {
    // JSON
    namespace j_realtime {
        const std::string type = TOSTRING(realtime);
    }

    class realtime : public game::abstract_game {
    public:
        explicit realtime();
        explicit realtime(json& package);
        const std::string& type () const override;
        void serialize_concrete_player (int player_uid, json& package) override;
        void update (json& output) override;
    };

}

#endif //LOGIC_REALTIME_HPP
