#ifndef LOGIC_COMMAND_HPP
#define LOGIC_COMMAND_HPP

#include "../base/interfaces.hpp"

class command {
public:
    std::string type;
    json payload;

    command(const std::string& type, const json& payload);
};

command::command (const std::string& type, const json& payload) {

}


#endif //LOGIC_COMMAND_HPP
