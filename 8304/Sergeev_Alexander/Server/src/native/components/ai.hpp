#ifndef LOGIC_AI_HPP
#define LOGIC_AI_HPP

#include "../base/includes.hpp"

namespace com {
    // JSON
    namespace j_ai {
        const std::string type = TOSTRING(ai);
        const std::string is_online = TOSTRING(is_online); // : bool
    }

    class ai : public icomponent {
    public:
        const std::string& type () const override;
        void serialize_public (const ent::unit& owner, json& output) const override;
        void setup_prototype (ent::unit_prototype& prototype) override;
        void command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) override;
        void signal (ent::unit& owner, game::abstract_game& context, json& input) override;
        void update (ent::unit& owner, game::abstract_game& context) override;
    };
}

#endif //LOGIC_AI_HPP
