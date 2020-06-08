#include "game_elements/neutral_objects/concrete_objects/rock.h"

#include "rand_int.h"

#include <sstream>

Rock::Rock(const sf::Vector2i& pos):
    pos(pos), maxDurability(4), durability(4)
{}


Rock::Rock(const sf::Vector2i& pos, int dura):
    pos(pos), maxDurability(dura), durability(dura)
{}


Entity* Rock::copy() const{
    auto e = new Rock(getPosition(), maxDurability);
    e->setDurability(getDurability());
    return e;
}


void Rock::setPosition(int x, int y){
    pos = sf::Vector2i(x, y);
}


const sf::Vector2i& Rock::getPosition() const{
    return pos;
}


Object* Rock::destroy(){
    durability = 0;
    return nullptr;
}


Object* Rock::treat(){
    if(durability == 0) return nullptr;

    durability--;
    if(durability == 0){
        if(maxDurability == 1)
            return nullptr;

        RandInt random;
        int shard_d = random(1, maxDurability);
        return new Rock(pos, shard_d);
    }
    else return this;
}


void Rock::setDurability(int dura){
    durability = dura;
    if(durability > maxDurability) durability = maxDurability;
    if(durability < 0) durability = 0;
}


int Rock::getDurability() const{
    return durability;
}


int Rock::getScore() const{
    return maxDurability;
}


Object::Type Rock::getObjectType() const{
    return Object::NonUsable;
}


std::string Rock::getInfo() const{
    std::stringstream ss;

    ss << "Neutral object: "
       << "Rock" << std::endl;
    ss << "With durability: "
       << getDurability() << std::endl;
    ss << "Treat to get\n"
       << "production points" << std::endl;
    ss << "After treat, a new\n"
       << "stone can appear, but\n"
       << "but with less durability";

    return ss.str();
}


const std::string& Rock::getID() const{
    return id;
}


bool Rock::delete_p() const{
    return durability == 0;
}

