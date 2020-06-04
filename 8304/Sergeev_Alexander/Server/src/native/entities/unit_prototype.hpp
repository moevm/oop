#ifndef LOGIC_UNIT_PROTOTYPE_HPP
#define LOGIC_UNIT_PROTOTYPE_HPP

#include "../base/includes.hpp"
#include "../structs/parameter_map.hpp"
#include "../components/component_storage.hpp"


namespace ent {
    // JSON
    namespace j_unit_prototype { // : parameter_map
        const std::string prototype = TOSTRING(prototype); // : string?
        const std::string name = TOSTRING(name); // : string
        const std::string components = TOSTRING(components); // : list<string>
    }

    class unit_prototype : public stts::parameter_map {
    private:
        unit_prototype* prototype;
        std::string name;
        std::map<std::string, icomponent*> components; //TODO make with iterator?

    public:
        explicit unit_prototype (const std::string& nname, unit_prototype* nprototype = nullptr);
        explicit unit_prototype (json& package);
        void serialize (json& package) const override;
        void deserialize (json& package) override;

        const std::string& get_name () const;
        void add_component (const std::string& component_name); // Experimental feature preview bugged like unity3d

        void get_cache_public(const unit& head, json& output) const;
        void update (unit& head, game::abstract_game& game, int ttl = 128);
        void signal (ent::unit& head, game::abstract_game& game, const std::string& component_name, json& component_data, int ttl = 128);
        void command (ent::unit& sender, ent::unit& head, game::abstract_game& context, std::string component_name, json& component_data, int ttl = 128);

        template<typename T>
        bool has_parameter (const std::string& parameter_name, int ttl = 128);

        template<typename T>
        T get_parameter (const std::string& parameter_name, int ttl = 128);

        template<typename T>
        void ensure_parameter (const std::string& parameter_name, T data);

        template<typename T>
        void set_parameter (const std::string& parameter_name, T data);
    };

    template<typename T>
    bool unit_prototype::has_parameter (const std::string& parameter_name, int ttl) {
        if (--ttl <= 0) throw recursion_exception("128 layers of inheritance reached!");
        T result;
        if (get<T>(parameter_name, result)) return true;
        else if (prototype) return prototype->has_parameter<T>(parameter_name, ttl - 1);
        else return false;
    }

    template<typename T>
    T unit_prototype::get_parameter (const std::string& parameter_name, int ttl) {
        if (--ttl <= 0) throw recursion_exception("128 layers of inheritance reached!");
        T result;
        if (get<T>(parameter_name, result)) return result;
        else if (prototype) return prototype->get_parameter<T>(parameter_name, ttl - 1);
        else throw null_pointer_exception(parameter_name + " parameter wasn't found");
    }

    template<typename T>
    void unit_prototype::ensure_parameter (const std::string& parameter_name, T data) {
        if (!has_parameter<T>(parameter_name)) set(parameter_name, data);
    }

    template<typename T>
    void unit_prototype::set_parameter (const std::string& parameter_name, T data) {
        set(parameter_name, data);
    }
}


#endif //LOGIC_UNIT_PROTOTYPE_HPP
