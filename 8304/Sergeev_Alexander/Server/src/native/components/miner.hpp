#ifndef LOGIC_MINER_HPP
#define LOGIC_MINER_HPP

#include "../base/includes.hpp"

namespace com {
    // JSON
    namespace j_miner {
        const std::string type = TOSTRING(miner);
        const std::string is_stopped = TOSTRING(is_stopped); // : bool
        const std::string is_mining = TOSTRING(is_mining); // : bool
        const std::string mining_tikz = TOSTRING(move_target); // : int
    }

    namespace j_miner_signal { // TODO (maybe use mutable as flag
        const std::string type = TOSTRING(miner);
        const std::string is_mining = TOSTRING(is_mining); // : bool
    }

    class miner : public icomponent {
    public:
        const std::string& type () const override;
        void serialize_public (const ent::unit& owner, json& output) const override;
        void setup_prototype (ent::unit_prototype& prototype) override;
        void command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) override;
        void signal (ent::unit& owner, game::abstract_game& context, json& input) override;
        void update (ent::unit& owner, game::abstract_game& context) override;
    };
}


#endif //LOGIC_MINER_HPP
