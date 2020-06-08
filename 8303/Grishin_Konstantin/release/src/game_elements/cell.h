#ifndef CELL_H
#define CELL_H

#include <SFML/System/Vector2.hpp>
#include <string>

namespace sf {
    class RenderWindow;
}

class Entity;

class Cell
{
    friend class CellGrid;

private:
    const sf::Vector2i coordinates;
    Entity *entity = nullptr;
    std::string landscapeID = "empty";

    Cell(sf::Vector2i coordinates, const std::string& landscapeID);

public:
    virtual ~Cell(){}

    Entity* setEntity(Entity* entity);
    Entity* getEntity() const;
    Entity* pullEntity();

    const sf::Vector2i& getPos() const;
    const std::string setLandscapeID(const std::string& id);
    const std::string& getLandscapeID() const;
};

#endif // CELL_H
