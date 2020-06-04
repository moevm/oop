#ifndef LOGIC_AI_ATTACKER_HPP
#define LOGIC_AI_ATTACKER_HPP

#include "../base/includes.hpp"
#include "ai.hpp"

namespace com {
    // JSON
    namespace j_ai_attacker {
        const std::string type = TOSTRING(ai_attacker);
    }

    class ai_attacker : public ai {
    public:
        const std::string& type () const override;
        void command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) override;
        void update (ent::unit& owner, game::abstract_game& context) override;
    };
}

#endif //LOGIC_AI_ATTACKER_HPP
