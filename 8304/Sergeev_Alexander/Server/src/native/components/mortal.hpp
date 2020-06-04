#ifndef LOGIC_MORTAL_HPP
#define LOGIC_MORTAL_HPP

#include "../base/includes.hpp"

namespace com {
    // JSON
    namespace j_mortal {
        const std::string type = TOSTRING(mortal);
        const std::string armor = TOSTRING(armor); // float
        const std::string hp = TOSTRING(hp); // float
        const std::string evading_chance = TOSTRING(evading_chance); // float [0, 1]
        const std::string is_alive = TOSTRING(is_alive); // bool
    }

    namespace j_mortal_signal {
        const std::string type = TOSTRING(mortal);
    }

    class mortal : public icomponent {
    public:
        const std::string& type () const override;
        void serialize_public (const ent::unit& owner, json& package) const override;
        void setup_prototype (ent::unit_prototype& prototype) override;
        void command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) override;
        void signal (ent::unit& owner, game::abstract_game& context, json& input) override;
        void update (ent::unit& owner, game::abstract_game& context) override;

    };
}


#endif //LOGIC_MORTAL_HPP
