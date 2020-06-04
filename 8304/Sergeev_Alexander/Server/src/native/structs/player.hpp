#ifndef LOGIC_PLAYER_HPP
#define LOGIC_PLAYER_HPP

#include "../base/includes.hpp"
#include "parameter_map.hpp"

namespace game {class abstract_game;}

namespace stts {
    // JSON
    namespace j_player {
        const std::string team = TOSTRING(team); // : int
        const std::string parameters = TOSTRING(parameters); // : parameter_map
    }

    namespace player_params {
        const std::string money = TOSTRING(money); // : int
    }

    class player : public iserializable {
    private:
        int team;
        OBSOLETE parameter_map parameters;

    public:
        explicit player (int nteam = 0);
        explicit player (json& package);
        player (const player& copy);
        player& operator= (const player& copy);
        void serialize (json& package) const override;
        void deserialize (json& package) override;

        int get_team();

        template<typename P>
        bool get (const std::string& name, P& result) {
            // TODO static assert
            return parameters.get(name, result);
        }

        template<typename P>
        void set (const std::string& name, P data) {
            // TODO static assert
            parameters.set(name, data);
        }
    };
}

#endif //LOGIC_PLAYER_HPP