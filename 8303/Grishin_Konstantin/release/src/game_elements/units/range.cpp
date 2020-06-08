#include "range.h"

Range::Range(Team team, const sf::Vector2i& pos):
    team(team), pos(pos)
{}


void Range::setPosition(int x, int y){
    pos.x = x;
    pos.y = y;
}


const sf::Vector2i& Range::getPosition() const{
    return pos;
}


Team Range::getTeam() const{
    return team;
}


bool Range::delete_p() const{
    return toDelete;
}


void Range::setActionState(){
    setAttackState();
}


void Range::move(int x, int y){
    setMoveState();
    setPosition(x, y);
}


bool Range::isMovable() const{
    return (!moving && getHealth() > 0);
}


Unit::Type Range::getUnitType() const{
    return Unit::Range;
}
