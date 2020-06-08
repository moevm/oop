#ifndef GAMEINTERFACEMANAGER_H
#define GAMEINTERFACEMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <exception>

#include "GUI/game_interface.h"

namespace sf {
    class Texture;
}

class ResourceManager;

class GameInterfaceManager
{
public:
    struct file_not_open: public std::exception
    {
        const char * what() const throw()
        {
            return "File does not exist or does not have permissions";
        }
    };

    struct interface_parameters: public std::exception
    {
        interface_parameters(int error) : error(error){}
        const char * what() const throw()
        {
            switch(error){
            case 0:
                return "Not enough parameters";
            case 1:
                return "To many parameters";
            default:
                return "Unexpected exception";
            }
        }
    private:
        int error;
    };

    struct button_parameters: public std::exception
    {
        button_parameters(int error) : error(error){}
        const char * what() const throw()
        {
            switch(error){
            case -1:
                return "Bad line of button count";
            default:
                return "Bad line of button parameters";
            }
        }
        int what()
        {
            return (error < 0)?0:error;
        }
    private:
        int error;
    };

private:
    std::map<std::string, GameInterface*> interface_library;
    std::map<std::string, std::map<std::string, GameInterfaceButton*>> button_library;

    std::vector<std::string> parseString(const std::string& str);
    bool isNumber(const std::string& n);

public:
    GameInterfaceManager(){};
    ~GameInterfaceManager();

    void addInterface(const std::string& interface_id,
                      const std::string& interface_path,
                      const ResourceManager& rsc_mngr,
                      const std::string& parent = "");

    GameInterface& getInterface(const std::string& interface_id) const;
};

#endif // GAMEINTERFACEMANAGER_H
