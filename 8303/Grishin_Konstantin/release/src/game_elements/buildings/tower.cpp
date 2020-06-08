#include "game_elements/buildings/tower.h"

#include "game_elements/units/magic_unit_factory.h"
#include "game_elements/units/concrete_units.h"

#include <sstream>

Tower::Tower(Team team, const sf::Vector2i& pos, Rot rot):
    team(team), pos(pos), rot(rot)
{
    factory = new MagicUnitFactory(team);

    maxHealth = initial_max_health;
    health = initial_max_health;
}


Entity* Tower::copy() const{
    auto e = new Tower(getTeam(), getPosition(), rot);
    e->setHealth(health);

    return e;
}


Tower::~Tower(){
    delete factory;
}


void Tower::setPosition(int x, int y){
    pos = sf::Vector2i(x, y);
}


void Tower::update(float)
{}


void Tower::damage(float dmg){
    health -= dmg;
    if(health <= 0)
        toDelete = 1;
}


void Tower::setHealth(float hp){
    if(hp < 0) health = 0;
    else if(hp > maxHealth) health = maxHealth;
    else health = hp;
}


float Tower::getHealth() const{
    return health;
}


float Tower::getMaxHealth() const{
    return maxHealth;
}


Building::Rot Tower::getRotation() const{
    return rot;
}


const sf::Vector2i& Tower::getPosition() const{
    return pos;
}


class Unit* Tower::createUnit(Unit::Type type){
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


bool Tower::delete_p() const{
    return toDelete;
}


Team Tower::getTeam() const{
    return team;
}


std::string
Tower::getInfo() const{
    std::stringstream ss;

    ss << ((getTeam() == Team::Red)? "RED " : "BLU ")
       << "Tower" << std::endl;
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


const std::string& Tower::getID() const{
    return id;
}



