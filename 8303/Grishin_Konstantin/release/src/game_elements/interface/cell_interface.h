#ifndef CELLINTERFACE_H
#define CELLINTERFACE_H

#include <SFML/System/Vector2.hpp>
#include <exception>

namespace sf {
    class RenderWindow;
}

class Field;
class Cell;
class LandscapeLibrary;
class Landscape;
class ResourceManager;
class EntityInterface;

class CellInterface
{
public:
    struct empty_cell: public std::exception{
    private:
        const char* msg;
    public:
        size_t code;

        empty_cell(const char* msg, size_t code = 0):
            msg(msg), code(code) {}
        const char * what() const throw()
        {
            return msg;
        }
    };
    
private:
    const LandscapeLibrary &library;
    const Cell *cell;
    Field *field;

public:
    CellInterface(const Cell *cell, Field *field, const LandscapeLibrary& library);
    CellInterface(const CellInterface& other);
    CellInterface& operator=(const CellInterface& other);

    void draw(sf::RenderWindow& window, const ResourceManager &rsc_mngr);

    const sf::Vector2i& getPos() const;
    bool empty() const;
    bool isFree() const;

    EntityInterface getEntity() const;

    const Landscape& landscape() const;
};

#endif // CELLINTERFACE_H
