#ifndef LOGIC_NEUTRAL_WALKER_ATTACKER_HPP
#define LOGIC_NEUTRAL_WALKER_ATTACKER_HPP

#include "../base/includes.hpp"
#include "ai.hpp"

namespace com {
    // JSON
    namespace j_ai_walker {
        const std::string type = TOSTRING(ai_walker);
    }

    class ai_walker : public ai {
    public:
        const std::string& type () const override;
        void command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) override;
        void update (ent::unit& owner, game::abstract_game& context) override;
    };
}

#endif //LOGIC_NEUTRAL_WALKER_ATTACKER_HPP
