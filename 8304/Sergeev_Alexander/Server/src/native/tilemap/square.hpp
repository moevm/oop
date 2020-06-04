#ifndef LOGIC_SQUARE_HPP
#define LOGIC_SQUARE_HPP

#include "abstract_tilemap.hpp"

namespace tilemap {
    // JSON
    namespace j_square {
        const std::string type = TOSTRING(square);
    }

    class square : public abstract_tilemap {
    public:
        explicit square(const stts::vector2<int>& nscale = stts::vector2<int>(0, 0));
        explicit square(json& package);
        const std::string& type () const override;
        tile::base_tile& get_tile (int x, int y) override;
        void set_tile (int x, int y, tile::base_tile* item) override;
        bool is_valid (int x, int y) const override;
        std::vector<stts::vector2<int>> get_neighbours (int x, int y) override;
        float get_distance (int source_x, int source_y, int destination_x, int destination_y) override;
        std::list<stts::vector2<int>> get_path (int source_x, int source_y, int destination_x, int destination_y) override;
    };
}

#endif //LOGIC_SQUARE_HPP
