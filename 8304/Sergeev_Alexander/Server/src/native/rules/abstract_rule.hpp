#ifndef LOGIC_ABSTRACT_RULE_HPP
#define LOGIC_ABSTRACT_RULE_HPP

#include "../base/includes.hpp"
#include "../entities/unit.hpp"
#include "../structs/player.hpp"

namespace rules {
    class abstract_rule : public iserializable, public ityped {
    public:
        void serialize (json& package) const override;
        void deserialize (json& package) override;
        virtual bool is_finished (std::map<int, stts::player*> players, std::map<int, ent::unit*> units) const = 0;
    };
}

#endif //LOGIC_ABSTRACT_RULE_HPP
