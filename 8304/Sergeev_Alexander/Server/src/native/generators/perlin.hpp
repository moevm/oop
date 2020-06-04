#ifndef LOGIC_PERLIN_HPP
#define LOGIC_PERLIN_HPP

#include "abstract_generator.hpp"
#include "../base/includes.hpp"
#include "../structs/vector2.hpp"
#include "../utils/mathematics.hpp"

namespace generators {
    namespace j_perlin {
        const std::string type = TOSTRING(perlin);
        const std::string seed = TOSTRING(seed); // : int
        const std::string octaves = TOSTRING(octaves); // : int
        const std::string persistance = TOSTRING(persistance); // : float
        const std::string players_uid = TOSTRING(players_uid); // : list<int>
        const std::string tilemap_scale = TOSTRING(tilemap_scale); // : vector2<int>
    }

    class perlin : public abstract_generator {
    private:
        int seed;
        int octaves;
        float persistance;
        std::set<int> players_uid;
        stts::vector2<int> tilemap_scale;

    public:
        perlin(int nseed, int noctaves, float npersistance, std::set<int> nplayers_uid, const stts::vector2<int>& ntilemap_scale);
        explicit perlin(json& package);
        void serialize (json& package) const override;
        void deserialize (json& package) override;
        const std::string& type () const override;
        std::unique_ptr<game::abstract_game> generate () override;
    };
}


#endif //LOGIC_PERLIN_HPP
