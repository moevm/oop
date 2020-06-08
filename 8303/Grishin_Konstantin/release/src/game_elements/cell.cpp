#include "cell.h"

Cell::Cell(sf::Vector2i coordinates, const std::string& landscapeID):
    coordinates(coordinates), landscapeID(landscapeID)
{}


Entity* Cell::setEntity(Entity *entity){
    if(this->entity)
        return entity;
    this->entity = entity;
    return nullptr;
}


Entity* Cell::getEntity() const{
    return entity;
}


Entity* Cell::pullEntity(){
    Entity* toRet = entity;
    entity = nullptr;
    return toRet;
}


const sf::Vector2i& Cell::getPos() const{
    return coordinates;
}


const std::string& Cell::getLandscapeID() const{
    return landscapeID;
}


const std::string Cell::setLandscapeID(const std::string& id){
    auto old_id = landscapeID;
    landscapeID = id;
    return old_id;
}
