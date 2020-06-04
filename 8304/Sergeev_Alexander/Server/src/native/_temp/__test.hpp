#ifndef LOGIC___TEST_HPP
#define LOGIC___TEST_HPP

#include <iostream>
#include <string>
#include "../base/interfaces.hpp"
#include "../entities/unit_prototype.hpp"


class self_serializable {
private:
    self_serializable() = default;

public:
    json& serialize();
};


//client
// player -> json command -> switch? -> unit -> game_storage -> player -> <unit!> -> component? -> execute


// Command_1 -> unit_1
// unit_1 do switch from Command_1
// unit_1 executes Command_1 to Component_1
// Component_1 makes Command_2
// Component_1 gets unit_2
// unit_2 returns Component_2 to Component_1
// Component_1 executes Command_2 to Component_2

// Command_1 signals unit_1
// unit_1 do switch from Command_1
// unit_1 executes Command_1 to Component_1

// Component_1 gets unit_2
// Component_1 signals Command_2 to unit_2
// unit_2 do switch from Command_2
// unit_2 executes Command_2 to Component_2

// unit do signal to component
// component do execute



// unit u = new unit(gunner_prototype);

// class unit {


/// readonly
//    unit& prototype;
//    std::map<string, component>& components;



// }




#endif //LOGIC___TEST_HPP
