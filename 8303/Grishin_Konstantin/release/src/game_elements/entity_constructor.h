#ifndef ENTITYCONSTRUCTOR_H
#define ENTITYCONSTRUCTOR_H

#include "game_elements/level.h"


class CommonUnitFactory;
class MagicUnitFactory;
class WorkerUnitFactory;
class Entity;

class EntityConstructor
{
    CommonUnitFactory *red_common_factory;
    CommonUnitFactory *blu_common_factory;

    MagicUnitFactory *red_magic_factory;
    MagicUnitFactory *blu_magic_factory;

    WorkerUnitFactory *red_worker_factory;
    WorkerUnitFactory *blu_worker_factory;

    Entity* createWorker(const Level::entity_stats& stats);
    Entity* createCombat(const std::string& id, const Level::entity_stats& stats);
    Entity* createBuilding(const std::string& id, const Level::entity_stats& stats);
    Entity* createObject(const std::string& id, const Level::entity_stats& stats);

public:
    EntityConstructor();
    Entity* createEntity(const std::string& id, const Level::entity_stats& stats);
};

#endif // ENTITYCONSTRUCTOR_H
