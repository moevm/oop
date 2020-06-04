#ifndef LOGIC__TODO_HPP
#define LOGIC__TODO_HPP

#include "../base/includes.hpp"
#include "../structs/vector2.hpp"

/// Добавляем сюда все to do компоненты в виде классов и их зависимости (используемые параметры), как поля
/// Все 'delay' поля и прочие, относящиеся к конкретным компонентам, будут переименованы и станут универсальными

// Структурные компоненты (хранят данные):

class resource_storage_self {
    bool is_crawlable; // Можно ли вытаскивать ресурс извне
    int resource_count;
    int max_resource_count;
};

class storage {
    std::list<int> children_unit_uids;
    int capacity;
};

// Поведенческие внутренние компоненты (изменяют себя):

class resource_generator_self {
    float speed;
    int resource_count;
    int max_resource_count;
};

class move { // should teleport player
    stts::vector2<int> position; // TODO float
    stts::vector2<int> destination;
    int min_distance;
};

class move_to_unit {
    stts::vector2<int> position; // TODO float
    int target_unit_uid;
};

class move_pathfinding { // uses get_path()
    stts::vector2<int> position; // TODO float
    stts::vector2<int> destination;
    int min_distance;
    std::list<stts::vector2<int>> move_path;
};

class move_patrol {
    stts::vector2<int> position; // TODO float
    std::list<stts::vector2<int>> patrol_points;
    int current_point;
};

class move_to_nearest {
    std::string target_prototype_name;
};

class attackable { // takes damage from other units
    int defence; // or something
    // TODO
};

class mortal { // or this takes damage from other units
    int hp;
    int max_hp;
};

class hp_change_self {
    int change_per_tick; // can be positive or negative
    float hp_change_delay;
};

// Поведенческие внешние компоненты (изменяют других или параметры игрока):

class shop_upgrade { //?
    int upgrade_cost;
    int upgrade_name;
};

class attack {
    int damage; // TODO damage_type
    float delay;
    float min_distance;
    int target_unit_uid;// TODO get is unit visible from last frame cached data
};

class attack_raycast {
    int damage;
    float delay;
    float max_distance;
    float min_distance;
    int target_unit_uid;// TODO get is unit visible from last frame cached data
};

class attack_tile {
    int damage; // TODO damage_type
    float delay;
    float radius;
    float damage_multipiler_on_radius;
    float min_distance;
    stts::vector2<int> target_position;
    int target_unit_uid;// TODO get is unit visible from last frame cached data
};

class money_changer {
    int money_per_tick; // can be positive and negative
    float delay;
};

class resource_to_money_converter { //?
    int resource_per_tick;
    int money_per_tick;
    float cool_down;
};

class hacker {
    float time_to_hack;
    float min_distance;
};

// Поведенческие смешанные компоненты (изменяют и себя, и других):

class resource_crawl_to_unit {
    int target_resource_unit_uid;
    float speed;
    int min_distance;
    int max_resource_count;
};

// Порождающие компоненты (создают юнитов):

class factory {
    std::string prototype_name;
    int cost;
    float time;
};

class attack_physic_bullet { // rocket (literally attacks spawned unit, it moves then boom or something)
    std::string prototype_name;
    float delay;
    float max_distance;
    float min_distance;
    float spawn_radius;
    stts::vector2<int> target_position;
};

// Остальные компоненты (мысли вслух):

class invisible;

class spray_fire;

class mine; // attack on touch

class electricity; //maybe no, too hard



#endif //LOGIC__TODO_HPP
