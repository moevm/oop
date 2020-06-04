#ifndef LOGIC_UNIT_FACTORY_HPP
#define LOGIC_UNIT_FACTORY_HPP

#include "../base/includes.hpp"
#include "unit_prototype.hpp"
#include "unit.hpp"

namespace ent { // PATTERN : FACTORY
    // JSON
    namespace j_unit_factory {
        const std::string prototypes = TOSTRING(prototypes); // : map<std::string, unit_prototype>
        const std::string next_id = TOSTRING(next_id); // : int
    }

    class unit_factory : iserializable {
    private:
        std::map<std::string, unit_prototype*> prototypes;
        int next_id;

        int get_id();

    public:
        explicit unit_factory ();
        explicit unit_factory (json& package);
        void serialize (json& package) const override;
        void deserialize (json& package) override;

        unit_prototype* get_prototype(const std::string& prototype_name);
        void set_prototype(unit_prototype* prototype);
        unit* make_unit(const std::string& prototype_name, int player_uid);
    };
}

#endif //LOGIC_UNIT_FACTORY_HPP
