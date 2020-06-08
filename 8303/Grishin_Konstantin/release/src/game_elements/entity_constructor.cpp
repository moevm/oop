#include "entity_constructor.h"
#include <iostream>

#include "game_elements/units/common_unit_factory.h"
#include "game_elements/units/magic_unit_factory.h"
#include "game_elements/units/worker_unit_factory.h"

#include "game_elements/units/melee.h"
#include "game_elements/units/range.h"
#include "game_elements/units/nuker.h"

#include "game_elements/units/concrete_units/worker.h"

#include "game_elements/buildings/barrack.h"
#include "game_elements/buildings/base.h"
#include "game_elements/buildings/tower.h"

#include "game_elements/neutral_objects/concrete_objects.h"


EntityConstructor::EntityConstructor()
{
    red_common_factory = new CommonUnitFactory(Team::Red);
    blu_common_factory = new CommonUnitFactory(Team::Blu);

    red_magic_factory = new MagicUnitFactory(Team::Red);
    blu_magic_factory = new MagicUnitFactory(Team::Blu);

    red_worker_factory = new WorkerUnitFactory(Team::Red);
    blu_worker_factory = new WorkerUnitFactory(Team::Blu);
}


Entity* EntityConstructor::createEntity
(const std::string &id, const Level::entity_stats &stats)
{
    switch(stats.type){
    case Level::entity_stats::combat_stats:
        return createCombat(id, stats);
    case Level::entity_stats::worker_stats:
        return createWorker(stats);
    case Level::entity_stats::building_stats:
        return createBuilding(id, stats);
    case Level::entity_stats::object_stats:
        return createObject(id, stats);
    }
}


Entity* EntityConstructor::createCombat
(const std::string &id, const Level::entity_stats &stats)
{
    Unit *unit = nullptr;
    if(stats.team == Team::Red){
        if(id == "unit_knight")
            unit = red_common_factory->createMelee(stats.x, stats.y);

        if(id == "unit_troll")
            unit = red_magic_factory->createMelee(stats.x, stats.y);

        if(id == "unit_archer")
            unit = red_common_factory->createRange(stats.x, stats.y);

        if(id == "unit_atrons")
            unit = red_magic_factory->createRange(stats.x, stats.y);

        if(id == "unit_berserk")
            unit = red_common_factory->createNuker(stats.x, stats.y);

        if(id == "unit_wizard")
            unit = red_magic_factory->createNuker(stats.x, stats.y);
    }
    else if(stats.team == Team::Blu){
        if(id == "unit_knight")
            unit = blu_common_factory->createMelee(stats.x, stats.y);

        if(id == "unit_troll")
            unit = blu_magic_factory->createMelee(stats.x, stats.y);

        if(id == "unit_archer")
            unit = blu_common_factory->createRange(stats.x, stats.y);

        if(id == "unit_atrons")
            unit = blu_magic_factory->createRange(stats.x, stats.y);

        if(id == "unit_berserk")
            unit = blu_common_factory->createNuker(stats.x, stats.y);

        if(id == "unit_wizard")
            unit = blu_magic_factory->createNuker(stats.x, stats.y);
    }

    if (unit == nullptr) return nullptr;

    if(stats.dflt) return unit;

    unit->setHealth(stats.combat.health);
    unit->setSteps(stats.combat.steps);
    unit->setExtra(stats.combat.extraDamage);

    return unit;
}


Entity* EntityConstructor::createWorker
(const Level::entity_stats &stats)
{
    Worker *unit = nullptr;
    if(stats.team == Team::Red)
        unit = red_worker_factory->createWorker(stats.x, stats.y);
    if(stats.team == Team::Blu)
        unit = blu_worker_factory->createWorker(stats.x, stats.y);

    if(unit == nullptr) return nullptr;
    if(stats.dflt) return unit;

    unit->setHealth(stats.worker.health);
    unit->setSteps(stats.worker.steps);
    unit->setExtra(stats.worker.extraSteps);

    unit->setTarget(stats.worker.target_x,
                    stats.worker.target_y);



    return unit;
}


Entity* EntityConstructor::createBuilding
(const std::string &id, const Level::entity_stats &stats)
{
    if(stats.team == Team::Neutral) return nullptr;
    Building *building = nullptr;
    if(id == "building_base")
        building = new Base(stats.team, sf::Vector2i(stats.x, stats.y),
                            static_cast<Building::Rot>(stats.building.rotation));
    if(id == "building_barrack")
        building = new Barrack(stats.team, sf::Vector2i(stats.x, stats.y),
                               static_cast<Building::Rot>(stats.building.rotation));
    if(id == "building_tower")
        building = new Tower(stats.team, sf::Vector2i(stats.x, stats.y),
                             static_cast<Building::Rot>(stats.building.rotation));

    if(building == nullptr) return nullptr;
    building->setHealth(stats.building.health);
    return building;
}


Entity* EntityConstructor::createObject
(const std::string &id, const Level::entity_stats &stats)
{
    Object *obj = nullptr;
    if(id == "object_barrel")
        obj = new Barrel(sf::Vector2i(stats.x, stats.y));
    if(id == "object_rock")
        obj = new Rock(sf::Vector2i(stats.x, stats.y));
    if(id == "object_tree")
        obj = new Tree(sf::Vector2i(stats.x, stats.y));
    if(id == "object_healing_poition")
        obj = new HealingPoition(sf::Vector2i(stats.x, stats.y));
    if(id == "object_stamina_poition")
        obj = new StaminaPoition(sf::Vector2i(stats.x, stats.y));
    if(id == "object_strength_poition")
        obj = new StrengthPoition(sf::Vector2i(stats.x, stats.y));

    if(obj == nullptr) return nullptr;
    if(stats.dflt) return obj;
    obj->setDurability(stats.object.durability);
    return obj;
}





