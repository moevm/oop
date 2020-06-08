#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <string>
#include <map>

class MenuState
{
public:
    std::string event_pressed = "";
    std::map<std::string, float> settings;
};

#endif // MENUSTATE_H
