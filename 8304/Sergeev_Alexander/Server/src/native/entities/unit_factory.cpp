#include "unit_factory.hpp"
#include "unit.hpp"
#include "unit_prototype.hpp"

int ent::unit_factory::get_id () {
    return next_id++;
}

ent::unit_factory::unit_factory () {
    next_id = 1;
    prototypes = std::map<std::string, unit_prototype*>();
}

ent::unit_factory::unit_factory (json& package) {
    unit_factory::deserialize(package);
}

void ent::unit_factory::serialize (json& package) const {
    package[j_unit_factory::next_id] = next_id;
    for (const auto& i : prototypes) {
        i.second->serialize(package[j_unit_factory::prototypes][i.first]);
    }
}

void ent::unit_factory::deserialize (json& package) {
    next_id = package[j_unit_factory::next_id].get<int>();
    for (auto& i : package[j_unit_factory::prototypes].items()) {
        prototypes[i.key()] = new unit_prototype(i.value());
    }
}

ent::unit_prototype* ent::unit_factory::get_prototype (const std::string& prototype_name) {
    if (prototypes[prototype_name] == nullptr) {
        throw null_pointer_exception("No such prototype " + prototype_name);
    }
    return prototypes[prototype_name];
}

void ent::unit_factory::set_prototype (unit_prototype* prototype) {
    if (prototypes[prototype->get_name()] != nullptr) {
        throw conflict_exception("This prototype already set");
    }
    prototypes[prototype->get_name()] = prototype; // FIXME memory leak
}

ent::unit* ent::unit_factory::make_unit (const std::string& prototype_name, int player_uid) {
    if (prototypes[prototype_name] == nullptr) {
        throw null_pointer_exception("Prototype for this unit does not exist " + prototype_name);
    }
    return new ent::unit(get_prototype(prototype_name), player_uid, get_id());
}



