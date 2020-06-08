#ifndef ENTITYINTERFACE_H
#define ENTITYINTERFACE_H

#include <SFML/System/Vector2.hpp>
#include <map>
#include <vector>
#include <string>

#include "game_elements/entity.h"

namespace sf {
    class RenderWindow;
}

class ResourceManager;
class Field;

class EntityInterface
{
    inline static const std::string empty_id = "nothing";
    const Entity* entity;
    Field* field;
    
    std::vector<std::pair<sf::Vector2i, float>>
    possibleWays;                               // all cells where UNIT can go

    std::vector<sf::Vector2i> targets;          // all ENEMY UNITS, which COMBAT unit can attack
                                                // and NEAR FREE cells, where WORKER can build
                                                // or destroy nature objects

public:
    EntityInterface(const Entity* entity, Field* field = nullptr);
    EntityInterface(const EntityInterface& other);
    EntityInterface& operator=(const EntityInterface& other);

    void draw(sf::RenderWindow& window, const ResourceManager& rsc_mngr);
    void drawSelector(sf::RenderWindow &window, const ResourceManager& rsc_mngr);
    
    void calculateWays();
    void calculateTargets();
    
    const std::vector<std::pair<sf::Vector2i, float>>& getWays() const;
    const std::vector<sf::Vector2i>& getTargets() const;

    sf::Vector2i getPos() const;

    void clear();
    bool empty() const;

    Team getTeam() const;
    Entity::Type getEntityType() const;
    const std::string& getID() const;
    std::string getInfo() const;

    bool operator==(const EntityInterface& other) const;
};

#endif // ENTITYINTERFACE_H
