#include "game_interface_manager.h"
#include <fstream>
#include <iostream>

#include "GUI/resource_manager.h"


GameInterfaceManager::~GameInterfaceManager(){
    for(auto interface: interface_library){
        delete interface.second;
        for(auto button: button_library[interface.first]){
            delete button.second;
        }
    }
}


std::vector<std::string>
GameInterfaceManager::parseString(const std::string& str){
    auto eraseSpaces = [](std::string& str){
        bool exit_flag = 0;
        auto it = str.begin();
        while(!exit_flag){
            if(isspace(*it)){
                str.erase(it);
                it = str.begin();
            }
            else exit_flag = 1;
        }

        exit_flag = 0;
        it = str.end()--;
        while(!exit_flag){
            if(isspace(*it)){
                str.erase(it);
                it = str.end()--;
            }
            else exit_flag = 1;
        }
    };

    std::vector<std::string> tokens;
    const char delim = ';';

    auto start = 0U;
    auto end = str.find(delim);
    while(end != std::string::npos)
    {
        auto token = str.substr(start, end-start);
        eraseSpaces(token);
        if(!token.empty())
            tokens.push_back(token);
        start = end + 1;
        end = str.find(delim, start);
    }

    auto token = str.substr(start, end-start);
    eraseSpaces(token);

    if(!token.empty())
        tokens.push_back(token);
    return tokens;
}


bool GameInterfaceManager::isNumber(const std::string &n){
    auto it = n.begin();
    while(it != n.end() && std::isdigit(*it)) ++it;

    return (!n.empty() && it == n.end());
}


void GameInterfaceManager::addInterface(const std::string &interface_id,
                                        const std::string &interface_path,
                                        const ResourceManager &rsc_mngr,
                                        const std::string &parent)
{
    std::ifstream file(interface_path);
    if(!file.is_open()){
        throw file_not_open();
    }

    std::string parameters_line;
    std::getline(file, parameters_line);

    auto parameters = parseString(parameters_line);
    if(parameters.size() < 2){
        throw interface_parameters(0);
    }
    if(parameters.size() > 2){
        throw interface_parameters(1);
    }

    auto interface = new GameInterface(interface_id, parameters[0],
                                       rsc_mngr.getTexture(parameters[1]),
                                       (interface_library.count(parent))?interface_library[parent]:nullptr);

    std::string cnt_line;
    std::getline(file, cnt_line);

    if(!isNumber(cnt_line))
    {
        delete interface;
        throw button_parameters(-1);
    }

    size_t cnt = std::atoi(cnt_line.c_str());
    std::vector<GameInterfaceButton*> buttons;
    for(size_t i = 0; i < cnt; i++){
        std::string button_line_p;
        std::getline(file, button_line_p);
        auto button_p = parseString(button_line_p);

        if(button_p.size() != 7){
            for(auto b: buttons){
                delete b;
            }
            delete interface;
            throw button_parameters(i);
        }

        if(!isNumber(button_p[4]) || !isNumber(button_p[5]) || !isNumber(button_p[6])){
            for(auto b: buttons){
                delete b;
            }
            delete interface;
            throw button_parameters(i);
        }

        int pos_x = std::atoi(button_p[4].c_str());
        int pos_y = std::atoi(button_p[5].c_str());
        int delay = std::atoi(button_p[6].c_str());

        auto button = new GameInterfaceButton(button_p[0],
                                              button_p[1],
                                              rsc_mngr.getTexture(button_p[2]),
                                              rsc_mngr.getTexture(button_p[3]));
        buttons.push_back(button);
        interface->addButton(*button, pos_x, pos_y);
        if(delay) button->setTimeToLive(delay);
    }
    interface_library[interface_id] =  interface;
    for(auto b: buttons){
        button_library[interface_id][b->getID()] = b;
    }
}


GameInterface& GameInterfaceManager::getInterface(const std::string &interface_id) const{
    return *(interface_library.at(interface_id));
}
