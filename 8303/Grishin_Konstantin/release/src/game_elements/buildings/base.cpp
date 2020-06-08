#include "base.h"

#include "game_elements/units/worker_unit_factory.h"
#include "game_elements/units/concrete_units/worker.h"

#include <sstream>

Base::~Base(){
    delete factory;
}


Base::Base(Team team, const sf::Vector2i& pos, Rot rot):
    team(team), pos(pos), rot(rot)
{
    factory = new WorkerUnitFactory(team);

    maxHealth = initial_max_health;
    health = initial_max_health;
}


Entity* Base::copy() const{
    auto e = new Base(getTeam(), getPosition(), rot);
    e->setHealth(health);

    return e;
}


void Base::update(float){
    /// do nothing
}


void Base::setPosition(int x, int y){
    pos = sf::Vector2i(x, y);
}


void Base::damage(float dmg){
    health -= dmg;
    if(health <= 0)
        toDelete = 1;
}


void Base::setHealth(float hp){
    if(hp < 0) health = 0;
    else if(hp > maxHealth) health = maxHealth;
    else health = hp;
}


float Base::getHealth() const{
    return health;
}


float Base::getMaxHealth() const{
    return maxHealth;
}


Building::Rot Base::getRotation() const{
    return rot;
}


const sf::Vector2i& Base::getPosition() const{
    return pos;
}


class Unit* Base::createUnit(Unit::Type type){
    if(type != Unit::Worker)
        return nullptr;

    sf::Vector2i offset;
    switch (rot){
    case Building::Up:
        offset = sf::Vector2i(0, -1);
        break;
    case Building::Right:
        offset = sf::Vector2i(1, 0);
        break;
    case Building::Down:
        offset = sf::Vector2i(0, 1);
        break;
    case Building::Left:
        offset = sf::Vector2i(-1, 0);
        break;
    }

    auto unit = factory->createWorker(pos.x + offset.x, pos.y + offset.y);
    return unit;
}


bool Base::delete_p() const{
    return toDelete;
}


Team Base::getTeam() const{
    return team;
}


std::string
Base::getInfo() const{
    std::stringstream ss;

    ss << ((getTeam() == Team::Red)? "RED " : "BLU ")
       << "Base" << std::endl;
    ss << "Health: " << getHealth() << "/" << getMaxHealth() << std::endl;
    ss << "Facing: ";
    switch(rot){
    case Building::Up:
        ss << "North";
        break;
    case Building::Right:
        ss << "East";
        break;
    case Building::Down:
        ss << "South";
        break;
    case Building::Left:
        ss << "West";
    }

    return ss.str();
}


const std::string& Base::getID() const{
    return  id;
}
