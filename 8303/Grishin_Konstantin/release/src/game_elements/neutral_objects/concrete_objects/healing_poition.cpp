#include "healing_poition.h"

#include "game_elements/units/unit.h"

#include <sstream>

HealingPoition::HealingPoition(const sf::Vector2i& pos):
    pos(pos)
{}


Entity* HealingPoition::copy() const{
    auto e = new HealingPoition(getPosition());
    e->setDurability(getDurability());
    return e;
}


void HealingPoition::setPosition(int x, int y){
    pos = sf::Vector2i(x, y);
}


const sf::Vector2i& HealingPoition::getPosition() const{
    return pos;
}


Object * HealingPoition::destroy(){
    toDelete = 1;
    return nullptr;
}


Object * HealingPoition::treat(){
    return destroy();
}


Object * HealingPoition::operator>>(class Unit *target){
    if(target->getHealth() == target->getMaxHealth())
        return this;
    target->heal(4);
    toDelete = 1;
    return nullptr;
}


void HealingPoition::setDurability(int dura){
    if(dura > 0)
        toDelete = 0;
    else
        toDelete = 1;
}


int HealingPoition::getDurability() const{
    return !toDelete;
}


int HealingPoition::getScore() const{
    return 0;
}


Object::Type HealingPoition::getObjectType() const{
    return Object::Usable;
}


std::string HealingPoition::getInfo() const{
    std::stringstream ss;

    ss << "Neutral object: "
       << "Healing poition" << std::endl;
    ss << "Combat units can use it" << std::endl << std::endl;

    ss << "If unit doesn't have\n"
       << "maximum health, it will\n"
       << "heal it, and then fade away" << std::endl;
    ss << "Otherwise, there'll be\n"
       << "no interaction, and object\n"
       << "will remain on map";

    return ss.str();
}


const std::string& HealingPoition::getID() const{
    return id;
}


bool HealingPoition::delete_p() const{
    return toDelete;
}






