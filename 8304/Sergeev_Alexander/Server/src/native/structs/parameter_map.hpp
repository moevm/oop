#ifndef LOGIC_PARAMETER_MAP_HPP
#define LOGIC_PARAMETER_MAP_HPP

#include "../base/includes.hpp"
#include "vector2.hpp"

namespace stts {
    // JSON
    namespace j_parameter_map {
        const std::string parameters_bool = TOSTRING(parameters_bool); // : map<string, bool>
        const std::string parameters_int = TOSTRING(parameters_int); // : map<string, int>
        const std::string parameters_float = TOSTRING(parameters_float); // : map<string, float>
        const std::string parameters_string = TOSTRING(parameters_string); // : map<string, string>
        const std::string parameters_vector2_int = TOSTRING(parameters_vector2_int); // : map<string, vector2<int>>
        const std::string parameters_vector2_float = TOSTRING(parameters_vector2_float); // : map<string, vector2<float>>
        const std::string parameters_list_vector2 = TOSTRING(parameters_list_vector2); // : map<string, std::list<vector2<int>>>
    }

    class parameter_map : iserializable {
    private:
        std::map<std::string, bool> parameters_bool;
        std::map<std::string, int> parameters_int;
        std::map<std::string, float> parameters_float;
        std::map<std::string, std::string> parameters_string;
        std::map<std::string, vector2<int>> parameters_vector2_int;
        std::map<std::string, vector2<float>> parameters_vector2_float;
        std::map<std::string, std::list<vector2<int>>> parameters_list_vector2;
        // //std::map<std::string, ibuffable> parameters_buffs; TODO

    public:
        parameter_map (); // TODO copy constructor (player uses)
        parameter_map (json& package);
        void serialize (json& package) const override;
        void deserialize (json& package) override;

        template<typename T>
        bool get (const std::string& name, T& data) const; // TODO allocates memory

        template<typename T>
        void set (const std::string& name, T data);
    };

    template<typename T>
    bool parameter_map::get (const std::string& name, T& data) const {
        throw unimplemented_exception(name + " parameter_map::get was not implemented yet");
    }

    template<typename T>
    void parameter_map::set (const std::string& name, const T data) {
        throw unimplemented_exception(name + " parameter_map::set was not implemented yet");
    }

    template <>
    bool parameter_map::get (const std::string& name, bool& data) const;

    template <>
    bool parameter_map::get (const std::string& name, int& data) const;

    template <>
    bool parameter_map::get (const std::string& name, float& data) const;

    template <>
    bool parameter_map::get (const std::string& name, std::string& data) const;

    template <>
    bool parameter_map::get (const std::string& name, vector2<int>& data) const;

    template <>
    bool parameter_map::get (const std::string& name, vector2<float>& data) const;

    template <>
    bool parameter_map::get (const std::string& name, std::list<vector2<int>>& data) const;


    template <>
    void parameter_map::set (const std::string& name, bool data);

    template <>
    void parameter_map::set (const std::string& name, int data);

    template <>
    void parameter_map::set (const std::string& name, float data);

    template <>
    void parameter_map::set (const std::string& name, std::string data);

    template <>
    void parameter_map::set (const std::string& name, vector2<int> data);

    template <>
    void parameter_map::set (const std::string& name, vector2<float> data);

    template <>
    void parameter_map::set (const std::string& name, std::list<vector2<int>> data);
}


#endif //LOGIC_PARAMETER_MAP_HPP
