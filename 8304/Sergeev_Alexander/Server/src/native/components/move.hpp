#ifndef LOGIC_MOVE_HPP
#define LOGIC_MOVE_HPP

#include "../base/includes.hpp"

namespace com {
    // JSON
    namespace j_move {
        const std::string type = TOSTRING(move);
        const std::string is_moving = TOSTRING(is_moving); // : bool
        const std::string is_stopped = TOSTRING(is_stopped); // : bool
        const std::string move_target = TOSTRING(move_target); // : vector2<int>
        const std::string move_path = TOSTRING(move_path); // list<vector2<int>>
    }

    namespace j_move_signal { // TODO (maybe use mutable as flag
        const std::string type = TOSTRING(move);
        const std::string is_moving = TOSTRING(is_moving); // : bool
        const std::string move_target = TOSTRING(move_target); // : vector2<int>
    }

    class move : public icomponent {
    public:
        const std::string& type () const override;
        void serialize_public (const ent::unit& owner, json& output) const override;
        void setup_prototype (ent::unit_prototype& prototype) override;
        void command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) override;
        void signal (ent::unit& owner, game::abstract_game& context, json& input) override;
        void update (ent::unit& owner, game::abstract_game& context) override;
    };
}

#endif //LOGIC_MOVE_HPP
