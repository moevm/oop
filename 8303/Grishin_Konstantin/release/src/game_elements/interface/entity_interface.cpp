#define __DEBUG__

#include "entity_interface.h"
#include <iostream>

#include "game_elements/units/concrete_units.h"
#include "game_elements/landscape/landscape.h"
#include "game_elements/buildings/building.h"
#include "game_elements/field.h"

#include "GUI/resource_manager.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


EntityInterface::EntityInterface(const Entity* entity, Field* field):
    entity(entity), field(field)
{}


EntityInterface::EntityInterface(const EntityInterface& other):
    entity(other.entity), field(other.field),
    possibleWays(other.possibleWays), targets(other.targets)
{}


EntityInterface&
EntityInterface::operator=(const EntityInterface& other)
{
    if(this != &other){
        entity = other.entity;
        field = other.field;
        
        possibleWays = other.possibleWays;
        targets = other.targets;
    }
    return *this;
}


void EntityInterface::draw(sf::RenderWindow &window, const ResourceManager &rsc_mngr){
    if(!entity) return;

    std::string entity_id;
    if(entity->getTeam() == Team::Blu)
        entity_id = "blu_";
    if(entity->getTeam() == Team::Red)
        entity_id = "red_";

    entity_id += entity->getID();

    sf::Sprite sprite;
    if(entity->getEntityType() == Entity::Building){
        auto building = static_cast<const Building*>(entity);
        switch (building->getRotation()) {
        case Building::Up:{
#ifdef __DEBUG__

            try{
                sprite.setTexture(rsc_mngr.getTexture(entity_id + "_up"));
            } catch (ResourceManager::unknown_resource e) {
                std::cerr << e.what() << ": " << e.str << std::endl;
                exit(1);
            }
#else
            sprite.setTexture(rsc_mngr.getTexture(entity_id + "_up"));
#endif
            break;
        }

        case Building::Right:{
#ifdef __DEBUG__
            try{
                sprite.setTexture(rsc_mngr.getTexture(entity_id + "_right"));
            } catch (ResourceManager::unknown_resource e) {
                std::cerr << e.what() << ": " << e.str << std::endl;
                exit(1);
            }
#else
            sprite.setTexture(rsc_mngr.getTexture(entity_id + "_right"));
#endif

            break;
        }
        case Building::Down:{
#ifdef __DEBUG__
            try{
                sprite.setTexture(rsc_mngr.getTexture(entity_id + "_down"));
            } catch (ResourceManager::unknown_resource e) {
                std::cerr << e.what() << ": " << e.str << std::endl;
                exit(1);
            }
#else
            sprite.setTexture(rsc_mngr.getTexture(entity_id + "_down"));
#endif
            break;
        }
        case Building::Left:{
#ifdef __DEBUG__
            try{
                sprite.setTexture(rsc_mngr.getTexture(entity_id + "_right"));
            } catch (ResourceManager::unknown_resource e) {
                std::cerr << e.what() << ": " << e.str << std::endl;
                exit(1);
            }
#else
            sprite.setTexture(rsc_mngr.getTexture(entity_id + "_right"));
#endif
            auto size = rsc_mngr.getTexture(entity_id + "_right").getSize();
            sprite.setTextureRect(sf::IntRect(size.x, 0, -size.x, size.y));
            break;
        }
        }
    }
    else{
#ifdef __DEBUG__
        try{
            sprite.setTexture(rsc_mngr.getTexture(entity_id));
        } catch (ResourceManager::unknown_resource e) {
            std::cerr << e.what() << ": " << e.str << std::endl;
            exit(1);
        }
#else
        sprite.setTexture(rsc_mngr.getTexture(entity_id));
#endif
    }

    auto size = sprite.getGlobalBounds();
    sprite.setOrigin(0, size.height/2);

    if(entity->getEntityType() == Entity::Unit){
        auto unit = dynamic_cast<const Unit*>(entity);
        sf::Vector2f currPos = sf::Vector2f(size.width*entity->getPosition().x,
                                            size.width*entity->getPosition().y);
        currPos += sf::Vector2f(size.width*unit->getMovingOffset().x,
                                size.width*unit->getMovingOffset().y);
        sprite.setPosition(currPos.x, currPos.y);
    }
    else{
        sprite.setPosition(size.width*entity->getPosition().x,
                           size.width*entity->getPosition().y);
    }

    window.draw(sprite);
    if(entity->getEntityType() != Unit::Object && entity->delete_p()){
#ifdef __DEBUG__
        try{
            sprite.setTexture(rsc_mngr.getTexture("killed"));
        }
        catch(ResourceManager::unknown_resource e)
        {
            std::cerr << e.what() << ": " << e.str << std::endl;
            exit(1);
        }
#else
        sprite.setTexture(rsc_mngr.getTexture("killed"));
#endif

        sprite.setPosition(size.width*entity->getPosition().x,
                           size.width*entity->getPosition().y);
        window.draw(sprite);
    }
}


void EntityInterface::drawSelector(sf::RenderWindow &window, const ResourceManager &rsc_mngr)
{
    if(empty()) return;
    if(entity->getEntityType() != Entity::Unit) return;

    std::string entity_id = "outline_";
    if(entity->getTeam() == Team::Blu)
        entity_id += "blu_";
    if(entity->getTeam() == Team::Red)
        entity_id += "red_";

    entity_id += entity->getID();
    if(auto u = dynamic_cast<const Unit*>(entity)){
        if(u->getMovingOffset() == sf::Vector2f(0, 0))
        {
            sf::Texture texture;
            try {
                texture = rsc_mngr.getTexture(entity_id);
            } catch (ResourceManager::unknown_resource) {
                std::cout << "Trying to get unknown resource: " << entity_id << std::endl;
                return;
            }

            sf::Sprite sprite(texture);
            auto size = sprite.getGlobalBounds();
            sprite.setOrigin(0, size.height/2);

            sprite.setPosition(size.width*entity->getPosition().x,
                               size.width*entity->getPosition().y);

            window.draw(sprite);
        }
    }
}


void EntityInterface::calculateWays(){
    possibleWays.clear();
    if(entity->getEntityType() != Entity::Unit) return;

    auto unit = dynamic_cast<const Unit*>(entity);

    struct Vertex{
        sf::Vector2i pos;
        float power;
    };

    std::vector<Vertex> vStepConductor;
    vStepConductor.push_back(Vertex{unit->getPosition(), unit->getSteps()});

    while(!vStepConductor.empty()){
        auto vertex = vStepConductor.back();

        bool isIn = 0;
        for(auto &pos: possibleWays)
            if(pos.first == vertex.pos)
                isIn = 1;

        if(!isIn)
            possibleWays.emplace_back(vertex.pos, vertex.power);

        vStepConductor.pop_back();

        if(vertex.power > 0){
            sf::Vector2i neighbours[4];

            //upper cell
            neighbours[0] = vertex.pos + sf::Vector2i(0, -1);

            //lower cell
            neighbours[1] = vertex.pos + sf::Vector2i(0, 1);

            //left cell
            neighbours[2] = vertex.pos + sf::Vector2i(1, 0);

            //right cell
            neighbours[3] = vertex.pos + sf::Vector2i(-1, 0);

            for(size_t i = 0; i < 4; i++)
            {
                auto cell = field->getCell(neighbours[i].x, neighbours[i].y);
                if(!cell.empty()){
                    if(cell.landscape().getType() == Landscape::Open && cell.isFree()){
                        auto neighbour_power = vertex.power - cell.landscape().getMoveCost();
                        if(neighbour_power >= 0){
                            vStepConductor.push_back(Vertex{neighbours[i], neighbour_power});
                        }
                    }
                }
            }
        }
    }

    if(!possibleWays.empty()){
        possibleWays.erase(possibleWays.begin());
    }
}


void EntityInterface::calculateTargets(){
    targets.clear();
    if(entity->getEntityType() != Entity::Unit) return;

    auto unit = dynamic_cast<const Unit*>(entity);

    struct Vertex{
        sf::Vector2i pos;
        int power;
    };

    int radius;
    int blind;

    switch(unit->getUnitType()){
    case Unit::Melee:
    case Unit::Worker:
        radius = 1;
        blind = 0;
        break;

    default:
        radius = unit->action().attackAction.radius;
        blind = unit->action().attackAction.blind;
        break;
    }

    std::vector<Vertex> vTargetsConductor;
    vTargetsConductor.push_back(Vertex{unit->getPosition(), radius});

    std::vector<Vertex> vVisitedTargets;

    while(!vTargetsConductor.empty()){
        auto vertex = vTargetsConductor.back();

        bool isIn = 0;
        for(auto &visited: vVisitedTargets)
            if(visited.pos == vertex.pos)
                isIn = 1;

        if(!isIn){
            vVisitedTargets.push_back(vertex);
        }

        vTargetsConductor.pop_back();

        if(vertex.power > 0){
            sf::Vector2i neighbours[4];

            //upper cell
            neighbours[0] = vertex.pos + sf::Vector2i(0, -1);

            //lower cell
            neighbours[1] = vertex.pos + sf::Vector2i(0, 1);

            //left cell
            neighbours[2] = vertex.pos + sf::Vector2i(1, 0);

            //right cell
            neighbours[3] = vertex.pos + sf::Vector2i(-1, 0);

            for(size_t i = 0; i < 4; i++)
            {
                auto cell = field->getCell(neighbours[i].x, neighbours[i].y);
                if(!cell.empty()){
                    auto neighbour_power = vertex.power - 1;
                    vTargetsConductor.push_back(Vertex{neighbours[i], neighbour_power});
                }
            }
        }
    }

    for(const auto& vertex: vVisitedTargets){
        auto delta = vertex.pos - entity->getPosition();
        if(abs(delta.x) + abs(delta.y) <= blind) continue;

        auto cell = field->getCell(vertex.pos.x, vertex.pos.y);

        if(unit->getUnitType() == Unit::Worker){
            if(!cell.isFree() && cell.getEntity().getEntityType() == Entity::Object)
                targets.emplace_back(vertex.pos);
        } else {
            if(!cell.isFree() && cell.getEntity().getEntityType() != Entity::Object
            && cell.getEntity().getTeam() != entity->getTeam())
                targets.emplace_back(vertex.pos);
        }
    }
}


const std::vector<std::pair<sf::Vector2i, float>>& EntityInterface::getWays() const{
    return possibleWays;
}


const std::vector<sf::Vector2i>& EntityInterface::getTargets() const{
    return targets;
}


sf::Vector2i EntityInterface::getPos() const{
    if(entity)
        return entity->getPosition();
    return sf::Vector2i(-1, -1);
}


void EntityInterface::clear(){
    entity = nullptr;
    field = nullptr;

    possibleWays.clear();
    targets.clear();
}


bool EntityInterface::empty() const{
    return !entity;
}


Team EntityInterface::getTeam() const{
    return entity->getTeam();
}


Entity::Type EntityInterface::getEntityType() const{
    return entity->getEntityType();
}


const std::string& EntityInterface::getID() const{
    if(entity){
        return entity->getID();
    }
    return empty_id;
}


std::string
EntityInterface::getInfo() const{
    if(entity)
        return entity->getInfo();
    return std::string();
}


bool EntityInterface::operator==(const EntityInterface& other) const{
    return entity == other.entity;
}


