#ifndef LOGIC_UNIT_HPP
#define LOGIC_UNIT_HPP

#include "../base/includes.hpp"
#include "unit_prototype.hpp"

namespace game { class abstract_game; }

namespace ent {
    // JSON
    namespace j_unit {
        const std::string prototype = TOSTRING(prototype); // : unit_prototype
        const std::string player_uid = TOSTRING(player_uid); // : int
        const std::string id = TOSTRING(id); // : int
    }

    class unit : protected stts::parameter_map {
    private:
        unit_prototype* prototype;
        int player_uid;
        int id;

        mutable bool is_dirty;
        mutable json cache;
        mutable json cache_public;

    public:
        explicit unit (unit_prototype* nprototype = nullptr, int nplayer_id = -1, int nid = -1);
        explicit unit (game::abstract_game& context, json& package);
        void serialize (json& package) const final;
        void deserialize (json& package) final;
        void serialize_public(json& package) const;

        void set_prototype (unit_prototype* nprototype);
        void set_dirty();

        int get_player_id ();
        int get_id ();

        void update (game::abstract_game& context); // Server -> Unit
        void signal (game::abstract_game& context, std::string component_name, json& component_data); // User -> Unit
        void command (unit& sender, game::abstract_game& context, std::string component_name, json& component_data); // Unit -> Unit

        template<typename T>
        bool has_parameter (const std::string& parameter_name) const;

        template<typename T>
        T get_parameter (const std::string& parameter_name) const;

        template<typename T>
        void ensure_parameter (const std::string& parameter_name, T data);

        template<typename T>
        void set_parameter (const std::string& parameter_name, T data);

    private:
        void ensure_cache() const;
    };

    template<typename T>
    bool unit::has_parameter (const std::string& parameter_name) const {
        T result;
        if (get<T>(parameter_name, result)) return true;
        else if (prototype) return prototype->has_parameter<T>(parameter_name);
        else return false;
    }

    template<typename T>
    T unit::get_parameter (const std::string& parameter_name) const {
        T result;
        if (get<T>(parameter_name, result)) return result;
        else if (prototype) return prototype->get_parameter<T>(parameter_name);
        else throw null_pointer_exception(parameter_name + " parameter wasn't found");
    }

    template<typename T>
    void unit::ensure_parameter (const std::string& parameter_name, T data) {
        if (!has_parameter<T>(parameter_name)) set(parameter_name, data);
    }

    template<typename T>
    void unit::set_parameter (const std::string& parameter_name, T data) {
        set(parameter_name, data);
    }
}


#endif //LOGIC_UNIT_HPP
