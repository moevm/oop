#include "game_elements/field.h"

#include <string>
#include <iostream>

#include "game_elements/cell_grid.h"
#include "game_elements/cell.h"
#include "game_elements/landscape/landscape_library.h"
#include "game_elements/landscape/plain_ls.h"
#include "game_elements/landscape/rough_ls.h"
#include "game_elements/landscape/canyon_ls.h"

#include "game_elements/entity.h"
#include "game_elements/entity_container.h"

#include "game_elements/master.h"

#include "game_elements/units/unit.h"
#include "game_elements/units/concrete_units.h"

#include "game_elements/buildings/building.h"
#include "game_elements/buildings/base.h"
#include "game_elements/buildings/tower.h"
#include "game_elements/buildings/barrack.h"

#include "game_elements/neutral_objects/usable.h"
#include "entity_constructor.h"

#include "game_elements/level.h"

#include "logger.h"

Field::~Field(){
    delete grid;
    delete landscapeLibrary;
    delete entities;
    delete obs;
}


Field::Field(const Level& lvl, Logger *logger):
    uWidth(lvl.width), uHeight(lvl.height),
    uMaxEntites(unsigned(uWidth*uHeight)),
    logger(logger)
{
    if(logger)
        (*logger) << "initialize field:\n";

    grid = new CellGrid(uWidth, uHeight);

    for(int x = 0; x < int(uWidth); x++)
        for(int y = 0; y < int(uHeight); y++)
        {
            int xy = y*uWidth+x;
            auto landscape = lvl.landscapes.at(lvl.field[xy]);
            grid->getCell(x, y)->setLandscapeID(landscape);
        }

    landscapeLibrary = new LandscapeLibrary;
    landscapeLibrary->addLandscape(new PlainLS);
    landscapeLibrary->addLandscape(new RoughLS);
    landscapeLibrary->addLandscape(new CanyonLS);

    entities = new EntityContainer;


    auto entity_constructor = new EntityConstructor;
    for (auto &e: lvl.entites){
        auto &id = lvl.entities_lib.at(e.first);

        auto entity = entity_constructor->createEntity(id, *(e.second));

        if(entity == nullptr) continue;
        if(!addEntity(entity, grid->getCell(entity->getPosition().x,
                                           entity->getPosition().y)))
        {
            delete entity;
        }
    }

    obs = new Master(this);

    if(logger)
        (*logger) << "field initialized\n";
}

Field::iterator Field::begin(){
    return iterator(this, grid->getBeg());
}


Field::iterator Field::end(){
    return iterator(this, grid->getEnd());
}


void Field::update(float ms_time){
    for(size_t i = 0; i < entities->size(); i++){
        (*entities)[i]->update(ms_time);
    }
}


std::pair<int, int> Field::gameStep(){
    // call master, which will deal with units
    return obs->checkEntities(logger);
}


sf::Vector2i Field::getSize() const{
    return sf::Vector2i(int(uWidth), int(uHeight));
}


Level Field::save() const{
    Level lvl;

    lvl.addLandscape("landscape_plain");
    lvl.addLandscape("landscape_rough");
    lvl.addLandscape("landscape_canyon");

    lvl.addEntity("unit_knight");
    lvl.addEntity("unit_troll");
    lvl.addEntity("unit_archer");
    lvl.addEntity("unit_atrons");
    lvl.addEntity("unit_berserk");
    lvl.addEntity("unit_wizard");
    lvl.addEntity("unit_worker");

    lvl.addEntity("building_base");
    lvl.addEntity("building_tower");
    lvl.addEntity("building_barrack");

    lvl.addEntity("object_barrel");
    lvl.addEntity("object_rock");
    lvl.addEntity("object_tree");

    lvl.addEntity("object_healing_poition");
    lvl.addEntity("object_stamina_poition");
    lvl.addEntity("object_strength_poition");

    lvl.width = uWidth;
    lvl.height = uHeight;
    lvl.field = new unsigned int[uWidth *uHeight];
    for(size_t xy = 0; xy < uWidth * uHeight; xy++){
        int x = xy%uWidth;
        int y = xy/uWidth;

        unsigned int l_id;
        if(grid->getCell(x, y)->getLandscapeID() == "landscape_plain")
            l_id = 1;
        if(grid->getCell(x, y)->getLandscapeID() == "landscape_rough")
            l_id = 2;
        if(grid->getCell(x, y)->getLandscapeID() == "landscape_canyon")
            l_id = 3;

        lvl.field[xy] = l_id;
    }

    for(size_t i = 0; i < entities->size(); i++){
        auto e = entities->at(i);
        unsigned int e_id;

        auto stats = new Level::entity_stats;
        stats->x = e->getPosition().x;
        stats->y = e->getPosition().y;
        stats->team = e->getTeam();

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "unit_knight")
        {
            e_id = 1;
            stats->type = Level::entity_stats::combat_stats;
            stats->combat.health = dynamic_cast<Unit*>(e)->getHealth();
            stats->combat.steps = dynamic_cast<Unit*>(e)->getSteps();
            stats->combat.extraDamage = dynamic_cast<Unit*>(e)->getExtra();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "unit_troll")
        {
            e_id = 2;
            stats->type = Level::entity_stats::combat_stats;
            stats->combat.health = dynamic_cast<Unit*>(e)->getHealth();
            stats->combat.steps = dynamic_cast<Unit*>(e)->getSteps();
            stats->combat.extraDamage = dynamic_cast<Unit*>(e)->getExtra();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "unit_archer")
        {
            e_id = 3;
            stats->type = Level::entity_stats::combat_stats;
            stats->combat.health = dynamic_cast<Unit*>(e)->getHealth();
            stats->combat.steps = dynamic_cast<Unit*>(e)->getSteps();
            stats->combat.extraDamage = dynamic_cast<Unit*>(e)->getExtra();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "unit_atrons")
        {
            e_id = 4;
            stats->type = Level::entity_stats::combat_stats;
            stats->combat.health = dynamic_cast<Unit*>(e)->getHealth();
            stats->combat.steps = dynamic_cast<Unit*>(e)->getSteps();
            stats->combat.extraDamage = dynamic_cast<Unit*>(e)->getExtra();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "unit_berserk")
        {
            e_id = 5;
            stats->type = Level::entity_stats::combat_stats;
            stats->combat.health = dynamic_cast<Unit*>(e)->getHealth();
            stats->combat.steps = dynamic_cast<Unit*>(e)->getSteps();
            stats->combat.extraDamage = dynamic_cast<Unit*>(e)->getExtra();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "unit_wizard")
        {
            e_id = 6;
            stats->type = Level::entity_stats::combat_stats;
            stats->combat.health = dynamic_cast<Unit*>(e)->getHealth();
            stats->combat.steps = dynamic_cast<Unit*>(e)->getSteps();
            stats->combat.extraDamage = dynamic_cast<Unit*>(e)->getExtra();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "unit_worker")
        {
            e_id = 7;
            stats->type = Level::entity_stats::worker_stats;
            stats->worker.health = dynamic_cast<Worker*>(e)->getHealth();
            stats->worker.steps = dynamic_cast<Worker*>(e)->getSteps();
            stats->worker.extraSteps = dynamic_cast<Worker*>(e)->getExtra();
            stats->worker.target_x = dynamic_cast<Worker*>(e)->getTarget().x;
            stats->worker.target_y = dynamic_cast<Worker*>(e)->getTarget().y;
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "building_base")
        {
            e_id = 8;
            stats->type = Level::entity_stats::building_stats;
            stats->building.health = dynamic_cast<Building*>(e)->getHealth();
            stats->building.rotation = dynamic_cast<Building*>(e)->getRotation();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "building_tower")
        {
            e_id = 9;
            stats->type = Level::entity_stats::building_stats;
            stats->building.health = dynamic_cast<Building*>(e)->getHealth();
            stats->building.rotation = dynamic_cast<Building*>(e)->getRotation();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "building_barrack")
        {
            e_id = 10;
            stats->type = Level::entity_stats::building_stats;
            stats->building.health = dynamic_cast<Building*>(e)->getHealth();
            stats->building.rotation = dynamic_cast<Building*>(e)->getRotation();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "object_barrel")
        {
            e_id = 11;
            stats->type = Level::entity_stats::object_stats;
            stats->object.durability = dynamic_cast<Object*>(e)->getDurability();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "object_rock")
        {
            e_id = 12;
            stats->type = Level::entity_stats::object_stats;
            stats->object.durability = dynamic_cast<Object*>(e)->getDurability();
        }


        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "object_tree")
        {
            e_id = 13;
            stats->type = Level::entity_stats::object_stats;
            stats->object.durability = dynamic_cast<Object*>(e)->getDurability();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "object_healing_poition")
        {
            e_id = 14;
            stats->type = Level::entity_stats::object_stats;
            stats->object.durability = dynamic_cast<Object*>(e)->getDurability();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "object_stamina_poition")
        {
            e_id = 15;
            stats->type = Level::entity_stats::object_stats;
            stats->object.durability = dynamic_cast<Object*>(e)->getDurability();
        }

        if(grid->getCell(e->getPosition().x, e->getPosition().y)->getEntity()->getID()
        == "object_strength_poition")
        {
            e_id = 16;
            stats->type = Level::entity_stats::object_stats;
            stats->object.durability = dynamic_cast<Object*>(e)->getDurability();
        }

        lvl.entites.emplace_back(e_id, stats);
    }

    return lvl;
}


CellInterface Field::getCell(int x, int y){
    auto cell = grid->getCell(x, y);
    CellInterface cell_interface(cell, this, *landscapeLibrary);
    return cell_interface;
}


bool Field::addEntity(Entity* entity, Cell* cell){
    if(logger)
        (*logger) << "\ttry to add entity " << entity->getID() << " to ("
                  << std::to_string(cell->getPos().x) << "; "
                  << std::to_string(cell->getPos().y) << ")\n";

    if(entities->size() >= uMaxEntites){
        if(logger)
            (*logger) << "\tfailed: to many entites on field\n";
        return 0;
    }

    cell->setEntity(entity);
    entities->push_back(entity);

    if(logger)
        (*logger) << "\tsuccess: entity added\n";

    return 1;
}


bool Field::createUnit(int creator_x, int creator_y, Unit::Type type){

    std::string unit_name;
    if(logger){
        if(type == Unit::Melee) unit_name = "melee unit";
        else if(type == Unit::Range) unit_name = "range unit";
        else if(type == Unit::Nuker) unit_name = "nuker unit";
        else if(type == Unit::Worker) unit_name = "worker unit";
        else unit_name = "unknown unit";

        (*logger) << "\ttry to create " <<  unit_name << " from ("
                  << std::to_string(creator_x) << "; "
                  << std::to_string(creator_y) << ")\n";
    }

    auto cell = grid->getCell(creator_x, creator_y);
    if(cell == nullptr){
        if(logger)
            (*logger) << "\tfailed: non-existent creator cell\n";
        return 0;
    }

    if(cell->getEntity() == nullptr){
        if(logger)
            (*logger) << "\tfailed: there is no entity on creator cell\n";

        return 0;
    }

    auto building = dynamic_cast<Building*>(cell->getEntity());
    if(building == nullptr){
        if(logger)
            (*logger) << "\tfailed: entity on cell ain't creator\n";

        return 0;
    }

    if(logger)
        (*logger) << "\tcreator found: " << building->getID() << "\n";

    auto unit = building->createUnit(type);
    if(unit == nullptr){
        if(logger)
            (*logger) << "\tfailed: " << building->getID()
                      << " can't create " << unit_name << "\n";

        return 0;
    }

    auto place_cell = grid->getCell(unit->getPosition().x, unit->getPosition().y);
    if(place_cell->getEntity() != nullptr){
        if(logger)
            (*logger) << "\tfailed: front of " << building->getID()
                      << " is occuped\n";

        delete unit;
        return 0;
    }

    if(!addEntity(unit, place_cell)){
        delete unit;
        return 0;
    }
    return 1;
}


bool Field::createBuilding(Team team, int type, int x, int y, int rot){
    auto cell = grid->getCell(x, y);

    std::string building_name;
    if(logger){
        if(type == Building::Base) building_name = "base building";
        else if(type == Building::Tower) building_name = "tower building";
        else if(type == Building::Barrack) building_name = "barrack building";
        else building_name = "unknown building";

        (*logger) << "\ttry to create " <<  building_name << " on ("
                  << std::to_string(x) << "; "
                  << std::to_string(y) << ")\n";
    }

    if(cell == nullptr){
        if(logger)
            (*logger) << "\tfailed: non-existent cell to build\n";
        return 0;
    }

    if(cell->getEntity()) {
        if(logger)
            (*logger) << "\tfailed: cell is occuped\n";

        return 0;
    }

    Building *building = nullptr;
    if(type == Building::Base){
        if(team == Team::Red){
            if(redBase){
                if(logger)
                    (*logger) << "\tfailed: red base already built\n";
            }
            else building = new Base(team, sf::Vector2i(x, y), static_cast<Building::Rot>(rot));
        }
        else if(team == Team::Blu){
            if(bluBase){
                if(logger)
                    (*logger) << "\tfailed: blu base already built\n";
            }
            else building = new Base(team, sf::Vector2i(x, y), static_cast<Building::Rot>(rot));
        }
        else
            if(logger)
                (*logger) << "\tfailed: can't build neutral base\n";
    }
    if(type == Building::Tower){
        building = new Tower(team, sf::Vector2i(x, y), static_cast<Building::Rot>(rot));
    }
    if(type == Building::Barrack){
        building = new Barrack(team, sf::Vector2i(x, y), static_cast<Building::Rot>(rot));
    }

    if(building == nullptr){
        if(logger)
            (*logger) << "\tfailed: unknown building type\n";

        return 0;
    }

    if(!addEntity(building, cell)){
        delete building;
        return 0;
    }
    return 1;
}


EntityInterface Field::getEntity(int x, int y){
    return EntityInterface(grid->getCell(x, y)->getEntity(), this);
}


EntityInterface Field::getRedBase()
{
    return EntityInterface(redBase, this);
}


EntityInterface Field::getBluBase()
{
    return EntityInterface(bluBase, this);
}


bool Field::moveUnit(int from_x, int from_y, int to_x, int to_y, float residualSteps){
    if(logger)
        (*logger) << "\ttry to move unit from ("
                  << std::to_string(from_x) << "; "
                  << std::to_string(from_y) << ") to ("
                  << std::to_string(to_x) << "; "
                  << std::to_string(to_y) << ")\n";

    auto from_cell = grid->getCell(from_x, from_y);
    if(!from_cell){
        if(logger)
            (*logger) << "\tfailed: non-existent \"from\" cell\n";

        return 0;
    }

    auto entity = from_cell->getEntity();
    if(!entity){
        if(logger)
            (*logger) << "\tfailed: there is no entity on \"from\" cell\n";

        return 0;
    }

    // call move from cell, where entity doesn't unit
    if(entity->getEntityType() != Entity::Unit){
        if(logger)
            (*logger) << "\tfailed: entity on \"from\" cell ain't unit\n";

        return 0;
    }

    auto unit = dynamic_cast<Unit*>(entity);

    if(!unit->isMovable()){
        if(logger)
            (*logger) << "\tfailed: unit locked for moving\n";

        return 0;
    }

    auto to_cell = grid->getCell(to_x, to_y);
    if(to_cell == nullptr) {
        if(logger)
            (*logger) << "\tfailed: try to move to non-existent cell\n";

        return 0;
    }

    if(to_cell->getEntity()){
        if(logger)
            (*logger) << "\tfailed: try to move to occuped cell\n";

        return 0;
    }

    // say to unit, that it's gonna be moved
    unit->move(to_x, to_y);
    unit->setSteps(residualSteps);

    // pull unit from cell
    from_cell->pullEntity();

    // put unit to other cell;
    to_cell->setEntity(unit);

    if(logger)
        (*logger) << "\tsuccess: unit moved\n";

    return 1;
}


bool Field::attack(int from_x, int from_y, int to_x, int to_y, float mod){
    if(logger)
        (*logger) << "\ttry to make an attack from ("
                  << std::to_string(from_x) << "; "
                  << std::to_string(from_y) << ") to ("
                  << std::to_string(to_x) << "; "
                  << std::to_string(to_y) << ")\n";

    auto from_cell = grid->getCell(from_x, from_y);
    if(!from_cell){
        if(logger)
            (*logger) << "\tfailed: non-existent attacking cell\n";

        return 0;
    }

    auto entity = from_cell->getEntity();
    if(!entity){
        if(logger)
            (*logger) << "\tfailed: there is no entity on attacking cell\n";

        return 0;
    }

    // call attack from cell, where entity ain't unit
    if(entity->getEntityType() != Entity::Unit){
        if(logger)
            (*logger) << "\tfailed: entity on attacking cell ain't unit\n";

        return 0;
    }

    auto unit = dynamic_cast<Unit*>(entity);

    // moving units can't attack
    if(!unit->isMovable()){
        if(logger)
            (*logger) << "\tfailed: unit locked to attack\n";

        return 0;
    }

    auto to_cell = grid->getCell(to_x, to_y);
    if(to_cell == nullptr){
        if(logger)
            (*logger) << "\tfailed: try to attack non-existent cell\n";

        return 0;
    }

    auto target = to_cell->getEntity();
    if(target == nullptr){
        if(logger)
            (*logger) << "\tfailed: there is not target on attacked cell\n";

        return 0;
    }

    // check, is the target damageable
    if(target->getEntityType() != Entity::Building
    && target->getEntityType() != Entity::Unit)
    {
        if(logger)
            (*logger) << "\tfailed: try to attack non-damageable entity\n";

        return 0;
    }

    // we have attacking unit and damageable object.
    // get damage of attacking, and direct it to damageable
    auto unit_action = unit->action();

    // unit on cell not able to attack
    if(unit_action.type != UnitAction::Attack) return 0;

    auto damage = unit_action.attackAction.damage;
    damage *= mod;

    // ... modify damage using cell(s) ...
    damage *= landscapeLibrary->getLandscape(from_cell->getLandscapeID()).getOutDmgMod();
    damage *= landscapeLibrary->getLandscape(to_cell->getLandscapeID()).getInDmgMod();

    std::cout << unit->getID() << " attacks " << target->getID() << std::endl;
    unit->setSteps(0);

    if(target->getEntityType() == Entity::Unit){
        dynamic_cast<Unit*>(target)->damage(damage, unit->getID());
    } else {
        dynamic_cast<Building*>(target)->damage(damage);
    }

    if(logger)
        (*logger) << "\tsuccess: " << unit->getID()
                  << " attacked " << target->getID() << "\n";

    unit->setActionState();
    return 1;
}


bool Field::work(int from_x, int from_y, int to_x, int to_y){
    if(logger)
        (*logger) << "\ttry to try to treat from ("
                  << std::to_string(from_x) << "; "
                  << std::to_string(from_y) << ") to ("
                  << std::to_string(to_x) << "; "
                  << std::to_string(to_y) << ")\n";

    auto from_cell = grid->getCell(from_x, from_y);
    if(!from_cell){
        if(logger)
            (*logger) << "\tfailed: non-existent worker cell\n";

        return 0;
    }

    auto entity = from_cell->getEntity();
    if(!entity){
        if(logger)
            (*logger) << "\tfailed: there is no worker on cell\n";

        return 0;
    }

    // can't call work from cell, where entity ain't unit
    if(entity->getEntityType() != Entity::Unit){
        if(logger)
            (*logger) << "\tfailed: try to work from cell where entity ain't unit\n";

        return 0;
    }
    auto unit = dynamic_cast<Unit*>(entity);

    // moving units can't work
    if(!unit->isMovable()){
        if(logger)
            (*logger) << "\tfailed: worker locked for work\n";

        return 0;
    }

    auto to_cell = grid->getCell(to_x, to_y);
    if(to_cell == nullptr){
        if(logger)
            (*logger) << "\tfailed: try to treat non-existent cell\n";

        return 0;
    }

    auto target = to_cell->getEntity();
    if(target == nullptr){
        if(logger)
            (*logger) << "\tfailed: try to treat empty cell\n";

        return 0;
    }

    if(target->getEntityType() != Entity::Object){
        if(logger)
            (*logger) << "\tfailed: try to treat non-object entity\n";

        return 0;
    }

    if(unit->getUnitType() != Unit::Worker){
        if(logger)
            (*logger) << "\tfailed: worker unit doesn't belong to worker class\n";

        return 0;
    }

    if(unit->action().workAction.work) return 0;

    if(logger)
        (*logger) << "\tsuccess: worked started to work\n";

    dynamic_cast<Worker*>(unit)->setTarget(to_cell->getPos().x, to_cell->getPos().y);
//    unit->setActionState();

    if(!unit->action().workAction.work)
    {
        dynamic_cast<Worker*>(unit)->setTarget(to_cell->getPos().x, to_cell->getPos().y);
//        unit->setActionState();
    }

    return 1;
}


bool Field::useItem(int user_x, int user_y, int item_x, int item_y){
    if(logger)
        (*logger) << "\ttry user ("
                  << std::to_string(user_x) << "; "
                  << std::to_string(user_y) << ") tries to use item on"
                  << std::to_string(item_x) << "; "
                  << std::to_string(item_y) << ")\n";

    auto item_cell = grid->getCell(item_x, item_y);
    if(!item_cell){
        if(logger)
            (*logger) << "\tfailed: try to use on non-existent cell\n";
        return 0;
    }

    auto entity = item_cell->getEntity();
    if(!entity){
        if(logger)
            (*logger) << "\tfailed: there is no any entity on item cell\n";

        return 0;
    }


    // can't use item from cell, where entity ain't item
    if(entity->getEntityType() != Entity::Object){
        if(logger)
            (*logger) << "\tfailed: entity on cell ain't object\n";

        return 0;
    }
    auto object = dynamic_cast<Object*>(entity);

    // can't use items, which ain't usable
    if(object->getObjectType() != Object::Usable){
        if(logger)
            (*logger) << "\tfailed: entity on cell ain't usable object\n";

        return 0;
    }

    auto user_cell = grid->getCell(user_x, user_y);
    if(!user_cell) {
        if(logger)
            (*logger) << "\tfailed: try to use item from non-existent cell\n";

        return 0;
    }

    auto user = user_cell->getEntity();
    if(!user){
        if(logger)
            (*logger) << "\tfailed: there is no any user\n";

        return 0;
    }

    if(user->getEntityType() != Entity::Unit){
        if(logger)
            (*logger) << "\tfailed: only units can use objects\n";

        return 0;
    }

    *dynamic_cast<Usable*>(object) >> dynamic_cast<Unit*>(user);

    if(logger)
        (*logger) << "\tsuccess: " << user->getID() << " used " << object->getID() << "\n";

    return 1;
}


bool Field::destroyItem(int x, int y){
    if(logger)
        (*logger) << "\ttry to destroy object on ("
                  << std::to_string(x) << "; "
                  << std::to_string(y) << ")\n";

    auto item_cell = grid->getCell(x, y);
    if(!item_cell){
        if(logger)
            (*logger) << "\tfailed: can't destroy object on non-existent cell\n";

        return 0;
    }

    auto entity = item_cell->getEntity();
    if(!entity){
        if(logger)
            (*logger) << "\tfailed: cell doesn't have any entity\n";

        return 0;
    }

    // can't destroy item from cell, where entity ain't item
    if(entity->getEntityType() != Entity::Object){
        if(logger)
            (*logger) << "\tfailed: entity on cell ain't object\n";

        return 0;
    }

    auto object = dynamic_cast<Object*>(entity);

    // set new entity without addEntity method
    // because there may not be free space (0.8 of all cells)
    // old item will be removed from cell, but not from container
    // master will free container after turn
    auto inheritor = object->destroy();  // after destroying, object can leave inheritor
                                         // just like barrel
    item_cell->pullEntity();
    item_cell->setEntity(inheritor);

    if(logger){
        (*logger) << "\tsuccess: " << object->getID() << "destroyed";
        if(inheritor != nullptr)
            (*logger) << "new object " << inheritor->getID() << " set\n";
    }

    return 1;
}

