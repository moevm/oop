#include "strength_poition.h"

#include "game_elements/units/unit.h"

#include <sstream>

StrengthPoition::StrengthPoition(const sf::Vector2i& pos):
    pos(pos)
{}


Entity* StrengthPoition::copy() const{
    auto e = new StrengthPoition(getPosition());
    e->setDurability(getDurability());
    return e;
}


void StrengthPoition::setPosition(int x, int y){
    pos = sf::Vector2i(x, y);
}


const sf::Vector2i& StrengthPoition::getPosition() const{
    return pos;
}


Object * StrengthPoition::destroy(){
    toDelete = 1;
    return nullptr;
}


Object * StrengthPoition::treat(){
    return destroy();
}


Object * StrengthPoition::operator>>(class Unit *target){
    target->increase(1);
    toDelete = 1;
    return nullptr;
}


void StrengthPoition::setDurability(int dura){
    if(dura > 0)
        toDelete = 0;
    else
        toDelete = 1;
}


int StrengthPoition::getDurability() const{
    return !toDelete;
}


int StrengthPoition::getScore() const{
    return 0;
}


Object::Type StrengthPoition::getObjectType() const{
    return Object::Usable;
}


std::string StrengthPoition::getInfo() const{
    std::stringstream ss;

    ss << "Neutral object: "
       << "Strength poition" << std::endl;
    ss << "Combat units can use it" << std::endl << std::endl;

    ss << "It will increase unit\n"
       << "damage, by one and then\n"
       << "fade away";

    return ss.str();
}


const std::string& StrengthPoition::getID() const{
    return id;
}


bool StrengthPoition::delete_p() const{
    return toDelete;
}
