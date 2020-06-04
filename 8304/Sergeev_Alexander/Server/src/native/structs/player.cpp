#include "player.hpp"

stts::player::player (int nteam) : team(nteam) {
    parameters = parameter_map();
}
stts::player::player (json& package) {
    player::deserialize(package);
}

stts::player::player (const player& copy) {
    *this = copy;
}

stts::player& stts::player::operator= (const player& copy) {
    if (this != &copy) {
        team = copy.team;
        parameters = parameter_map();
    }
    return *this;
}

void stts::player::serialize (json& package) const {
    package[j_player::team] = team;
    parameters.serialize(package[j_player::parameters]);
}

void stts::player::deserialize (json& package) {
    team = package[j_player::team].get<int>();
    parameters = parameter_map(package[j_player::parameters]);
}

int stts::player::get_team () {
    return team;
}


