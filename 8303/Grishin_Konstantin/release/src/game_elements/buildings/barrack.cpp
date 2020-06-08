#include "game_elements/buildings/barrack.h"

#include "game_elements/units/common_unit_factory.h"
#include "game_elements/units/concrete_units.h"

#include <sstream>

Barrack::Barrack(Team team, const sf::Vector2i& pos, Rot rot):
    team(team), pos(pos), rot(rot)
{
    factory = new CommonUnitFactory(team);

    maxHealth = initial_max_health;
    health = initial_max_health;
}


Entity* Barrack::copy() const{
    auto e = new Barrack(getTeam(), getPosition(), rot);
    e->setHealth(health);

    return e;
}


Barrack::~Barrack(){
    delete factory;
}


void Barrack::setPosition(int x, int y){
    pos = sf::Vector2i(x, y);
}


void Barrack::update(float)
{}


void Barrack::damage(float dmg){
    health -= dmg;
    if(health <= 0)
        toDelete = 1;
}


void Barrack::setHealth(float hp){
    if(hp < 0) health = 0;
    else if(hp > maxHealth) health = maxHealth;
    else health = hp;
}


float Barrack::getHealth() const{
    return health;
}


float Barrack::getMaxHealth() const{
    return maxHealth;
}


Building::Rot Barrack::getRotation() const{
    return rot;
}


const sf::Vector2i& Barrack::getPosition() const{
    return pos;
}


class Unit* Barrack::createUnit(Unit::Type type){
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
    class Unit* unit = nullptr;
    switch (type){
    case Unit::Melee:
        unit = factory->createMelee(pos.x + offset.x, pos.y + offset.y);
        break;
    case Unit::Range:
        unit = factory->createRange(pos.x + offset.x, pos.y + offset.y);
        break;
    case Unit::Nuker:
        unit = factory->createNuker(pos.x + offset.x, pos.y + offset.y);
        break;
    default: break;
    }

    return unit;
}


bool Barrack::delete_p() const{
    return toDelete;
}


Team Barrack::getTeam() const{
    return team;
}


std::string Barrack::getInfo() const{
    std::stringstream ss;

    ss << ((getTeam() == Team::Red)? "RED " : "BLU ")
       << "Barrack" << std::endl;
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


const std::string& Barrack::getID() const{
    return id;
}



