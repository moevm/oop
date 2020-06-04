#ifndef LOGIC_ABSTRACT_TILEMAP_HPP
#define LOGIC_ABSTRACT_TILEMAP_HPP

#include "../base/includes.hpp"
#include "../structs/vector2.hpp"
#include "../tiles/base_tile.hpp"
#include "../tiles/money_dealer.hpp"
#include "../tiles/damage_dealer.hpp"

namespace tilemap {
    namespace j_abstract_tilemap {
        const std::string scale = TOSTRING(scale); // : vector2<int>
        const std::string data = TOSTRING(data); // : base_tile[]
    }

    //TODO foreach iterator on tiles
    class abstract_tilemap : public iserializable, public ityped {
        OBSOLETE friend class nlohmann::json_tools;
    protected:
        stts::vector2<int> scale; // X - width, Y - height
        tile::base_tile** data;

    public:
        explicit abstract_tilemap (const stts::vector2<int>& nscale = stts::vector2<int>(0, 0));
        explicit abstract_tilemap (json& package);
        abstract_tilemap (const abstract_tilemap& copy);
        abstract_tilemap& operator= (const abstract_tilemap& copy);
        ~abstract_tilemap () override;
        void serialize (json& package) const override; // TODO cache and set_dirty!
        void deserialize (json& package) override;
        void serialize_public (json& package);

        tile::base_tile& operator[] (const stts::vector2<int>& position);
        tile::base_tile& get_tile (const stts::vector2<int>& position); // TODO into const tile&
        void set_tile (const stts::vector2<int>& position, tile::base_tile* item);
        bool is_valid(const stts::vector2<int>& position) const;
        std::vector<stts::vector2<int>> get_neighbours (const stts::vector2<int>& point);
        float get_distance (const stts::vector2<int>& source, const stts::vector2<int>& destination);
        std::list<stts::vector2<int>> get_path(const stts::vector2<int>& source, const stts::vector2<int>& destination);
        void transpose(ent::unit& target, const stts::vector2<int>& to_position);

        virtual tile::base_tile& get_tile (int x, int y) = 0;
        virtual void set_tile (int x, int y, tile::base_tile* item) = 0;
        virtual bool is_valid(int x, int y) const = 0;
        virtual std::vector<stts::vector2<int>> get_neighbours (int x, int y) = 0;
        virtual float get_distance (int source_x, int source_y, int destination_x, int destination_y) = 0;
        virtual std::list<stts::vector2<int>> get_path(int source_x, int source_y, int destination_x, int destination_y) = 0;

        void clear_tiles();
        stts::vector2<int>& get_scale();

    protected:
        int tile_count() const;
    };
}

#endif //LOGIC_ABSTRACT_TILEMAP_HPP
