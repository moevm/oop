#ifndef LOGIC_ATTACK_HPP
#define LOGIC_ATTACK_HPP

#include "../base/includes.hpp"

namespace com {
    // JSON
    namespace j_attack {
        const std::string type = TOSTRING(attack);
        const std::string damage = TOSTRING(damage); // : float
        const std::string attack_target = TOSTRING(attack_target); // : int (unit id)
        const std::string is_attacking = TOSTRING(is_attacking); // : bool
    }

    namespace j_attack_signal { // TODO (maybe use mutable as flag
        const std::string type = TOSTRING(attack);
        const std::string attack_target = TOSTRING(attack_target); // : int (unit id)
        const std::string is_attacking = TOSTRING(is_attacking); // : bool
    }

    class attack : public icomponent {
    public:
        const std::string& type () const override;
        void serialize_public (const ent::unit& owner, json& package) const override;
        void setup_prototype (ent::unit_prototype& prototype) override;
        void command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) override;
        void signal (ent::unit& owner, game::abstract_game& context, json& input) override;
        void update (ent::unit& owner, game::abstract_game& context) override;
    };
}

#endif //LOGIC_ATTACK_HPP
