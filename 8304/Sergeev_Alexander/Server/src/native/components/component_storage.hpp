#ifndef LOGIC_COMPONENT_STORAGE_HPP
#define LOGIC_COMPONENT_STORAGE_HPP

#include "../base/includes.hpp"
#include "storage.hpp"
#include "move.hpp"
#include "mortal.hpp"
#include "attack.hpp"
#include "spawner.hpp"
#include "locationable.hpp"
#include "miner.hpp"
#include "base.hpp"
#include "ai_walker.hpp"
#include "ai_attacker.hpp"


namespace com {
    class component_storage {
    private:
        component_storage() = default; // Static class
        static std::map<std::string, icomponent*> components;

    public:
        static icomponent* get_component (const std::string& component_name);
    };
}

#endif //LOGIC_COMPONENT_STORAGE_HPP
