#ifndef LOGIC_HEXAGONAL_HPP
#define LOGIC_HEXAGONAL_HPP

#include "abstract_tilemap.hpp"

namespace tilemap {
    // JSON
    namespace j_hexagonal {
        const std::string type = TOSTRING(hexagonal);
    }

    class hexagonal : public abstract_tilemap {
    public:
        explicit hexagonal(const stts::vector2<int>& nscale);
        explicit hexagonal(json& package);
        const std::string& type () const override;
        tile::base_tile& get_tile (int x, int y) override;
        void set_tile (int x, int y, tile::base_tile* item) override;
        bool is_valid (int x, int y) const override;
        std::vector<stts::vector2<int>> get_neighbours (int x, int y) override;
        float get_distance (int source_x, int source_y, int destination_x, int destination_y) override;
        std::list<stts::vector2<int>> get_path (int source_x, int source_y, int destination_x, int destination_y) override;
    };
}

#endif //LOGIC_HEXAGONAL_HPP
