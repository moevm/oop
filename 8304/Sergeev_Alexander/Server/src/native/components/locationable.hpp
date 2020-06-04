#ifndef LOGIC_LOCATIONABLE_HPP
#define LOGIC_LOCATIONABLE_HPP


#include "../base/includes.hpp"

namespace com {
    // WARNING: ALWAYS set FIRST
    // JSON
    namespace j_locationable {
        const std::string type = TOSTRING(locationable);
        const std::string position = TOSTRING(position); // : vector2<int>
    }

    class locationable : public icomponent {
    public:
        const std::string& type () const override;
        void serialize_public (const ent::unit& owner, json& output) const override;
        void setup_prototype (ent::unit_prototype& prototype) override;
        void command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) override;
        void signal (ent::unit& owner, game::abstract_game& context, json& input) override;
        void update (ent::unit& owner, game::abstract_game& context) override;
    };
}


#endif //LOGIC_LOCATIONABLE_HPP
