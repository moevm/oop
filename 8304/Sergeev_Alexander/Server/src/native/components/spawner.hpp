#ifndef LOGIC_SPAWNER_HPP
#define LOGIC_SPAWNER_HPP

#include "../base/includes.hpp"

namespace com {
    // JSON
    namespace j_spawner {
        const std::string type = TOSTRING(spawner);
        const std::string production_object = TOSTRING(production_object); // : string (prototype name)
        const std::string production_line = TOSTRING(production_line); // : int
        const std::string production_tikz = TOSTRING(production_tikz); // : int
        const std::string production_cost = TOSTRING(production_cost); // : int
        const std::string is_producing = TOSTRING(is_producing); // : bool
    }

    namespace j_spawner_signal { // TODO (maybe use mutable as flag
        const std::string type = TOSTRING(spawner);
        const std::string production_line = TOSTRING(production_line); // : int
    }

    class spawner : public icomponent {
    public:
        const std::string& type () const override;
        void serialize_public (const ent::unit& owner, json& output) const override;
        void setup_prototype (ent::unit_prototype& prototype) override;
        void command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) override;
        void signal (ent::unit& owner, game::abstract_game& context, json& input) override;
        void update (ent::unit& owner, game::abstract_game& context) override;
    };
}


#endif //LOGIC_SPAWNER_HPP
