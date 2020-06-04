#ifndef LOGIC_BASE_TILE_HPP
#define LOGIC_BASE_TILE_HPP

#include "../base/includes.hpp"
#include "../structs/vector2.hpp"

namespace ent { class unit; }

namespace tile {
    // JSON
    namespace j_base_tile {
        const std::string type = TOSTRING(base_tile);
        const std::string height = TOSTRING(height); // : float
        const std::string occupier_uid = TOSTRING(occupier_uid); // : int
    }

    class base_tile : public iserializable, public ityped {
    private:
        float height;
        int occupier_uid;

    public:
        // FOR PATH SEARCHING PURPOSES!!!

        int f, g, h;
        //stts::vector2<int> position;
        bool opened;
        bool closed;
        stts::vector2<int> parent;

        void clear();

        // FOR PATH SEARCHING PURPOSES NO MORE!!!

        explicit base_tile (float nheight = 0);
        explicit base_tile(json& package);
        base_tile (const base_tile& copy);
        base_tile& operator= (const base_tile& copy);
        void serialize (json& package) const override;
        void deserialize (json& package) override;
        void serialize_public (json& package);
        const std::string& type () const override;

        float get_height () const;
        void set_height (float nheight);
        int get_occupier_id () const;
        bool is_occupied () const;

        virtual void on_unit_enter (ent::unit& sender);
        virtual void on_unit_touch (ent::unit& sender, game::abstract_game& context);
        virtual void on_unit_exit (ent::unit& sender);

        void operator+= (ent::unit& unit);
        void operator-= (ent::unit& unit);
    };
}

#endif //LOGIC_BASE_TILE_HPP
