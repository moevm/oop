#include "cell_interface.h"

#define __DEBUG__

#include <iostream>

#include "game_elements/landscape/landscape_library.h"
#include "GUI/resource_manager.h"

#include "game_elements/cell.h"
#include "game_elements/units/unit.h"

#include "game_elements/interface/entity_interface.h"
#include "game_elements/field.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


CellInterface::CellInterface(const Cell *cell, Field *field, const LandscapeLibrary &library):
    library(library), cell(cell), field(field)
{}


CellInterface::CellInterface(const CellInterface& other):
    library(other.library), cell(other.cell), field(other.field)
{}


CellInterface&
CellInterface::operator=(const CellInterface& other){
    if(this != &other){
        cell = other.cell;
        field = other.field;
    }
    return *this;
}


void CellInterface::draw(sf::RenderWindow &window, const ResourceManager &rsc_mngr){
    if(cell == nullptr) return;

#ifdef __DEBUG__
    try {
        auto t = rsc_mngr.getTexture(cell->getLandscapeID());
    } catch (ResourceManager::unknown_resource e) {
        std::cerr << e.what() << ": " << e.str << std::endl;
        exit(1);
    }
#else
    auto t = rsc_mngr.getTexture(cell->getLandscapeID());
#endif

    sf::Sprite sprite(rsc_mngr.getTexture(cell->getLandscapeID()));

    auto size = sprite.getGlobalBounds();
    sprite.setPosition(size.width*cell->getPos().x, size.height*cell->getPos().y);
    window.draw(sprite);
}


const sf::Vector2i& CellInterface::getPos() const{
    if(empty())
        throw empty_cell("Trying to get position of non-existent cell", 1);
    return cell->getPos();
}


bool CellInterface::empty() const{
    return !cell;
}


bool CellInterface::isFree() const{
    if(empty()){
        throw empty_cell("Trying to check non-existent cell", 2);
    }

    if(cell->getEntity())
        return 0;
    return 1;
}


EntityInterface CellInterface::getEntity() const{
    if(empty())
        throw empty_cell("Trying to get entity from non-existent cell", 3);

    auto entity = cell->getEntity();
    if(entity && entity->getEntityType() == Entity::Unit && !dynamic_cast<Unit*>(entity)->isMovable())
        entity = nullptr;
    return EntityInterface(cell->getEntity(), field);
}


const Landscape& CellInterface::landscape() const{
    if(empty())
        throw empty_cell("trying to get landscape of non-existent cell", 4);
    return library.getLandscape(cell->getLandscapeID());
}


