#ifndef FIELD_H
#define FIELD_H

#include "SFML/System/Vector2.hpp"

// THERE SHOULD NOT BE ANY RULES
// FIELD - JUST CONTAINER FOR GAME OBJECTS
// GAME CLASS CREATES AND RULES THE FIELD !!!!!!!

#include "game_elements/team.h"
#include "game_elements/interface/cell_interface.h"
#include "game_elements/interface/entity_interface.h"

#include "game_elements/field_iterator.h"
#include "game_elements/entity.h"
#include "game_elements/units/unit.h"

namespace sf {
    class RenderWindow;
}

class CellGrid; // cells container
class LandscapeLibrary;

class Entity;
class EntityContainer;

class Building;
class Base;

class Level;
class Logger;

class Field
{
    friend class FieldIterator;
    
    // classes to control interactions of field objects
    friend class CellInterface;
    friend class EntityInterface;
    friend class Master; // controll units states (some kind of observer)
    
    // game space defining constants
    const unsigned int uWidth;
    const unsigned int uHeight;
    const unsigned int uMaxEntites;

    // cell grid or game space
    CellGrid *grid;

    // game landscapes
    LandscapeLibrary *landscapeLibrary;

    // container of pointers of all game objects
    // used for direct enities control
    EntityContainer *entities;

    Master *obs;

    // main entites of the player - bases
    Base *bluBase;
    Base *redBase;
    Logger *logger;

private:
    bool addEntity(Entity* entity, Cell* cell);

public:
    typedef FieldIterator iterator;
    typedef FieldIterator const_iterator;

    ~Field();
    Field(const Level& lvl, Logger *logger = nullptr);

    Level save() const;

    iterator begin();
    iterator end();

    sf::Vector2i getSize() const;

    // step of frame cycle
    void update(float ms_time);

    // step of game cycle
    // return points earned after cycle
    // <RED, BLU>
    std::pair<int, int> gameStep();

    bool createUnit(int creator_x, int creator_y, Unit::Type type);
    bool createBuilding(Team team, int type, int x, int y, int rot);
    void deleteEntity(int x, int y);

    // get an entity to issue a command to it
    EntityInterface getEntity(int x, int y);
    CellInterface getCell(int x, int y);

    EntityInterface getRedBase();
    EntityInterface getBluBase();

    // interractions between entites
    bool moveUnit(int from_x, int from_y, int to_x, int to_y, float residualSteps);
    bool attack(int from_x, int from_y, int to_x, int to_y, float mod = 1.f);
    bool work(int from_x, int from_y, int to_x, int to_y);
    bool useItem(int user_x, int user_y, int item_x, int item_y);
    bool destroyItem(int x, int y);

};

#endif // FIELD_H
