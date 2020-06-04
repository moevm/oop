#ifndef LOGIC_SKIRMISH_HPP
#define LOGIC_SKIRMISH_HPP

#include "abstract_rule.hpp"

namespace rules {
    // JSON
    namespace j_skirmish {
        const std::string type = TOSTRING(skirmish);
    }

    class skirmish : public abstract_rule {
    public:
        explicit skirmish();
        explicit skirmish(json& package);
        const std::string& type () const override;
    private:
        bool is_finished (std::map<int, stts::player*> players, std::map<int, ent::unit*> units) const override;
    };
}

#endif //LOGIC_SKIRMISH_HPP
