#include "neutral.hpp"

void Neutral::spotted (Unit* other) {
    if(team == NEUTRAL && other->getTeam() != NEUTRAL) {
        gameHandler->getLogger().log(getType() + " " + to_string(getId()) + " became " + (other->getTeam() == RED ? "RED" : "BLUE"));
        team = other->getTeam();
        setTargetXY(other->getTargetX(), other->getTargetY());
    }
}


