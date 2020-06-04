#ifndef LOGIC_DAMAGE_DEALER_HPP
#define LOGIC_DAMAGE_DEALER_HPP

#include "base_tile.hpp"

namespace tile {
    // JSON
    namespace j_damage_dealer {
        const std::string type = TOSTRING(damage_dealer);
        const std::string damage = TOSTRING(damage); // : int
    }

    class damage_dealer : public base_tile {
    private:
        int damage;

    public:
        explicit damage_dealer (float nheight = 0, int ndamage = 1);
        explicit damage_dealer (json& package);
        void serialize (json& package) const override;
        void deserialize (json& package) override;
        const std::string& type () const override;

        void on_unit_enter (ent::unit& sender) override;
        void on_unit_touch (ent::unit& sender, game::abstract_game& context) override;
        void on_unit_exit (ent::unit& sender) override;
    };
}


#endif //LOGIC_DAMAGE_DEALER_HPP
