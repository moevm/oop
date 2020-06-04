#ifndef LOGIC_SIMPLE_HPP
#define LOGIC_SIMPLE_HPP

#include "abstract_generator.hpp"
#include "../base/includes.hpp"
#include "../structs/vector2.hpp"
#include "../utils/mathematics.hpp"

namespace generators {
    namespace j_simple {
        const std::string type = TOSTRING(simple);
        const std::string seed = TOSTRING(seed); // : int
        const std::string players_uid = TOSTRING(players_uid); // : list<int>
        const std::string tilemap_scale = TOSTRING(tilemap_scale); // : vector2<int>
    }

    class simple : public abstract_generator {
    private:
        int seed;
        std::set<int> players_uid;
        stts::vector2<int> tilemap_scale;

    public:
        simple(int nseed, std::set<int> nplayers_uid, const stts::vector2<int>& ntilemap_scale);
        explicit simple(json& package);
        void serialize (json& package) const override;
        void deserialize (json& package) override;
        const std::string& type () const override;
        std::unique_ptr<game::abstract_game> generate () override;
    };
}


#endif //LOGIC_SIMPLE_HPP
