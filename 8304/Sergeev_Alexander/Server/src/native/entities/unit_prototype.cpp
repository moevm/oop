#include "unit_prototype.hpp"
#include "../game/abstract_game.hpp"


ent::unit_prototype::unit_prototype (const std::string& nname, unit_prototype* nprototype) {
    prototype = nprototype;
    name = nname;
    components = std::map<std::string, icomponent*>();
}

ent::unit_prototype::unit_prototype (json& package) {
    unit_prototype::deserialize(package);
}

void ent::unit_prototype::serialize (json& package) const {
    parameter_map::serialize(package);
    if (prototype) prototype->serialize(package[j_unit_prototype::prototype]);
    package[j_unit_prototype::name] = name;
    package[j_unit_prototype::components] = json::array();
    for (const auto& key : components) package[j_unit_prototype::components].push_back(key.second->type());
}

void ent::unit_prototype::deserialize (json& package) {
    parameter_map::deserialize(package);
    if (package.contains(j_unit_prototype::prototype)) prototype = new unit_prototype(package[j_unit_prototype::prototype]);
    else prototype = nullptr; // TODO optimize
    name = package[j_unit_prototype::name].get<std::string>();
    components = std::map<std::string, icomponent*>();
    for (const auto& componentName : package[j_unit_prototype::components]) components[componentName] = com::component_storage::get_component(componentName);
}

const std::string& ent::unit_prototype::get_name () const {
    return name;
}

void ent::unit_prototype::add_component (const std::string& component_name) {
    icomponent* component = com::component_storage::get_component(component_name);
    component->setup_prototype(*this);
    components[component_name] = component;
}

void ent::unit_prototype::get_cache_public (const ent::unit& head, json& output) const {
    for (const auto& i : components) i.second->serialize_public(head, output); // TODO recursive
}

void ent::unit_prototype::update (ent::unit& head, game::abstract_game& game, int ttl) {
    if (--ttl <= 0) throw recursion_exception("128 layers of inheritance reached!");
    for (const auto& i : components)
        if (i.second) {
            logger::say() << "\t" << "Updating component " << i.second->type() << "..." << logger::over;
            i.second->update(head, game);
        } else {
            logger::say(l::error) << "\t" << "Component is NULL, possible bug!" << logger::over;
        }
    if (prototype) prototype->update(head, game, ttl);
}

void ent::unit_prototype::signal (ent::unit& head, game::abstract_game& game, const std::string& component_name, json& component_data, int ttl) {
    if (--ttl <= 0) throw recursion_exception("128 layers of inheritance reached!");
    if (components.count(component_name) != 0) {
        components[component_name]->signal(head, game, component_data);
    }
    else if (prototype) {
        prototype->signal(head, game, component_name, component_data, ttl);
    }
    else {
        // There is no component in this unit you want to signal
        // TODO maybe have output from signal
    }
}

void ent::unit_prototype::command (ent::unit& sender, ent::unit& head, game::abstract_game& context, std::string component_name, json& component_data, int ttl) {
    if (--ttl <= 0) throw recursion_exception("128 layers of inheritance reached!");
    if (components.count(component_name) != 0) {
        components[component_name]->command(sender, head, context, component_data);
    }
    else if (prototype) {
        prototype->command(sender, head, context, component_name, component_data, ttl);
    }
    else {
        // There is no component in this unit you want to signal
        // TODO maybe have output from signal
    }
}






