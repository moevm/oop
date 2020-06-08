#include "stamina_poition.h"

#include "game_elements/units/unit.h"

#include <sstream>

StaminaPoition::StaminaPoition(const sf::Vector2i& pos):
    pos(pos)
{}


Entity* StaminaPoition::copy() const{
    auto e = new StaminaPoition(getPosition());
    e->setDurability(getDurability());
    return e;
}


void StaminaPoition::setPosition(int x, int y){
    pos = sf::Vector2i(x, y);
}


const sf::Vector2i& StaminaPoition::getPosition() const{
    return pos;
}


Object * StaminaPoition::destroy(){
    toDelete = 1;
    return nullptr;
}


Object * StaminaPoition::treat(){
    return destroy();
}


Object * StaminaPoition::operator>>(class Unit *target){
    if(target->getSteps() == target->getMaxSteps())
        return this;
    target->resetSteps();
    toDelete = 1;
    return nullptr;
}


void StaminaPoition::setDurability(int dura){
    if(dura > 0)
        toDelete = 0;
    else
        toDelete = 1;
}


int StaminaPoition::getDurability() const{
    return !toDelete;
}


int StaminaPoition::getScore() const{
    return 0;
}


Object::Type StaminaPoition::getObjectType() const{
    return Object::Usable;
}


std::string StaminaPoition::getInfo() const{
    std::stringstream ss;

    ss << "Neutral object: "
       << "Stamina poition" << std::endl;
    ss << "Combat units can use it" << std::endl << std::endl;

    ss << "If unit doesn't have\n"
       << "maximum steps, it will\n"
       << "set steps at maximum,\n"
       << "and then fade away"  << std::endl;
    ss << "Otherwise, there'll be\n"
       << "no interaction, and object\n"
       << "will remain on map";
    return ss.str();
}


const std::string& StaminaPoition::getID() const{
    return id;
}


bool StaminaPoition::delete_p() const{
    return toDelete;
}
