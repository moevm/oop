#ifndef LOGIC_ABSTRACT_GAME_HPP
#define LOGIC_ABSTRACT_GAME_HPP

#include "../base/includes.hpp"
#include "../structs/player.hpp"
#include "../tilemap/abstract_tilemap.hpp"
#include "../entities/unit_factory.hpp"
#include "../rules/abstract_rule.hpp"

namespace game {
    // JSON
    namespace j_abstract_game {
        const std::string factory = TOSTRING(factory); // : unit_factory?
        const std::string rule = TOSTRING(rule); // : abstract_rule?
        const std::string units = TOSTRING(units); // : map<int, unit>?
        const std::string players = TOSTRING(players); // map<int, player>?
        const std::string tilemap = TOSTRING(tilemap); // : abstract_tilemap?
    }

    namespace j_commands {
        const std::string sacrifice = TOSTRING(sacrifice);
    }

    class abstract_game : public iserializable, public iserializable_public, public ityped {
    protected:
        ent::unit_factory factory;
        std::unique_ptr<rules::abstract_rule> rule;
        std::map<int, ent::unit*> units; // TODO how to make no alloc without ptrs
        std::map<int, stts::player*> players;
        std::unique_ptr<tilemap::abstract_tilemap> tilemap;

    public:
        explicit abstract_game ();
        explicit abstract_game (json& package);
        void serialize (json& package) const override;
        void deserialize (json& package) override;
        void serialize_public (json& package) const override;
        virtual void serialize_concrete_player (int player_uid, json& package) = 0;

        virtual void update (json& output) = 0;
        void signal (json& input, json& output);
        bool is_finished () const;

        rules::abstract_rule& get_rule();
        void set_rule (std::unique_ptr<rules::abstract_rule> nrule);

        ent::unit_prototype* get_prototype(const std::string& prototype_name);
        void set_prototype(ent::unit_prototype* prototype);

        ent::unit& make_unit (const std::string& prototype_name, int player_uid);
        void unmake_unit (int id);
        ent::unit* get_unit (int id);
        int get_units_count();

        stts::player& get_player (int uid);
        void set_player (int uid, stts::player* nplayer);

        tilemap::abstract_tilemap& get_tilemap();
        void set_tilemap (std::unique_ptr<tilemap::abstract_tilemap> ntilemap);
    };
}

#endif //LOGIC_ABSTRACT_GAME_HPP
