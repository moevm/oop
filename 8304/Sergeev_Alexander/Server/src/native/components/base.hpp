#ifndef LOGIC_BASE_HPP
#define LOGIC_BASE_HPP

#include "../base/includes.hpp"

namespace com {
    // JSON
    namespace j_base {
        const std::string type = TOSTRING(base);
        const std::string is_defeated = TOSTRING(is_moving); // : bool
        const std::string defenders_tikz = TOSTRING(is_stopped); // : int
    }

    namespace j_base_signal {
        const std::string type = TOSTRING(base);
        const std::string is_defeated = TOSTRING(is_moving); // : bool
        const std::string defenders_tikz = TOSTRING(is_stopped); // : int
    }

    class base : public icomponent {
    public:
        const std::string& type () const override;
        void serialize_public (const ent::unit& owner, json& output) const override;
        void setup_prototype (ent::unit_prototype& prototype) override;
        void command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) override;
        void signal (ent::unit& owner, game::abstract_game& context, json& input) override;
        void update (ent::unit& owner, game::abstract_game& context) override;
    };
}

#endif //LOGIC_BASE_HPP
