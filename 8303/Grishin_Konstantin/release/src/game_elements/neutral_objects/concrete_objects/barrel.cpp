#include "game_elements/neutral_objects/concrete_objects/barrel.h"

#include "rand_int.h"

#include "game_elements/neutral_objects/concrete_objects/healing_poition.h"
#include "game_elements/neutral_objects/concrete_objects/stamina_poition.h"
#include "game_elements/neutral_objects/concrete_objects/strength_poition.h"

#include <sstream>

Barrel::Barrel(const sf::Vector2i& pos):
    pos(pos)
{}


Entity* Barrel::copy() const{
    auto e = new Barrel(getPosition());
    e->setDurability(getDurability());
    return e;
}


void Barrel::setPosition(int x, int y){
    pos = sf::Vector2i(x, y);
}


const sf::Vector2i& Barrel::getPosition() const{
    return pos;
}


Object* Barrel::destroy(){
    RandInt random;
    if(toDelete == 1) return nullptr;

    toDelete = 1;
    switch(random(1, 3)){
    case 1:
        return new HealingPoition(pos);
    case 2:
        return new StaminaPoition(pos);
    case 3:
        return new StrengthPoition(pos);
    default: return nullptr;
    }
}


Object* Barrel::treat(){
    return destroy();
}


void Barrel::setDurability(int dura){
    if(dura > 0)
        toDelete = 0;
    else
        toDelete = 1;
}


int Barrel::getDurability() const{
    return !toDelete;
}


int Barrel::getScore() const{
    return 0;
}


Object::Type Barrel::getObjectType() const{
    return Object::NonUsable;
}


std::string Barrel::getInfo() const{
    std::stringstream ss;

    ss << "Neutral object: "
       << "Barrel" << std::endl;
    ss << "Destroy or treat to get\n"
       << "random buff poition";

    return ss.str();
}


const std::string& Barrel::getID() const{
    return id;
}


bool Barrel::delete_p() const{
    return toDelete;
}






