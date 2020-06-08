#include "game_elements/units/melee.h"

Melee::Melee(Team team, const sf::Vector2i& pos):
    team(team), pos(pos)
{}


void Melee::setPosition(int x, int y){
    pos.x = x;
    pos.y = y;
}


const sf::Vector2i& Melee::getPosition() const{
    return pos;
}


Team Melee::getTeam() const{
    return team;
}


bool Melee::delete_p() const{
    return toDelete;
}


void Melee::setActionState(){
    setAttackState();
}


void Melee::move(int x, int y){
    setMoveState();
    setPosition(x, y);
}


bool Melee::isMovable() const{
    return (!moving && getHealth() > 0);
}


Unit::Type Melee::getUnitType() const{
    return Unit::Melee;
}




