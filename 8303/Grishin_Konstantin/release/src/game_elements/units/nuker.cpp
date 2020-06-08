#include "game_elements/units/nuker.h"

Nuker::Nuker(Team team, const sf::Vector2i& pos):
    team(team), pos(pos)
{}


void Nuker::setPosition(int x, int y){
    pos.x = x;
    pos.y = y;
}


const sf::Vector2i& Nuker::getPosition() const{
    return pos;
}


Team Nuker::getTeam() const{
    return team;
}


bool Nuker::delete_p() const{
    return toDelete;
}


void Nuker::setActionState(){
    setAttackState();
}


void Nuker::move(int x, int y){
    setMoveState();
    setPosition(x, y);
}


bool Nuker::isMovable() const{
    return (!moving && getHealth() > 0);;
}


Unit::Type Nuker::getUnitType() const{
    return Unit::Nuker;
}
