#include "component_storage.hpp"

std::map<std::string, icomponent*> com::component_storage::components = {{j_attack::type,  new attack()},
                                                                         {j_mortal::type,  new mortal()},
                                                                         {j_move::type,    new move()},
                                                                         {j_storage::type, new storage()},
                                                                         {j_spawner::type, new spawner()},
                                                                         {j_locationable::type, new locationable()},
                                                                         {j_miner::type,  new miner()},
                                                                         {j_base::type,  new base()},
                                                                         {j_ai_walker::type,  new ai_walker()},
                                                                         {j_ai_attacker::type,  new ai_attacker()}};

icomponent* com::component_storage::get_component (const std::string& component_name) {
    if (components[component_name] == nullptr) throw null_pointer_exception(component_name + " component is invalid");
    return components[component_name];
}