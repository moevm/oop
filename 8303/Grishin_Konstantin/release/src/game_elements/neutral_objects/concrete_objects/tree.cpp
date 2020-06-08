#include "tree.h"

#include <sstream>

Tree::Tree(const sf::Vector2i& pos):
    pos(pos), durability(4)
{}


Entity* Tree::copy() const{
    auto e = new Tree(getPosition());
    e->setDurability(getDurability());
    return e;
}


void Tree::setPosition(int x, int y){
    pos = sf::Vector2i(x, y);
}


const sf::Vector2i& Tree::getPosition() const{
    return pos;
}


Object * Tree::destroy(){
    durability = 0;
    return nullptr;
}


Object * Tree::treat(){
    if(durability == 0) return nullptr;

    durability--;
    if(durability == 0) return nullptr;
    else return this;
}


void Tree::setDurability(int dura){
    durability = dura;
    if (durability > 4) durability = 4;
    if (durability < 0) durability = 0;
}


int Tree::getDurability() const{
    return durability;
}


int Tree::getScore() const{
    return 2;
}


Object::Type Tree::getObjectType() const{
    return Object::NonUsable;
}


std::string Tree::getInfo() const{
    std::stringstream ss;

    ss << "Neutral object: "
       << "Tree" << std::endl;
    ss << "With durability: "
       << getDurability() << std::endl;
    ss << "Treat to get\n"
       << "production points" << std::endl;
    ss << "Will fade away\n"
       << "after treat";

    return ss.str();
}


const std::string& Tree::getID() const{
    return id;
}


bool Tree::delete_p() const{
    return durability == 0;
}

