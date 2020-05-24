#ifndef GAME_H
#define GAME_H

#include <memory>
#include "interface.h"
#include "gamerule.h"

template<class Rule>
class Game
{
public:
    Game()
    {
        rule = std::make_shared<Rule>();
        interface = std::make_unique<Interface>();
    }

    int Start_Game()
    {
        //unitCount = 10;
        int unitCount = std::dynamic_pointer_cast<GameRule>(rule)->get_UnitCount();
        return  interface->St_Game(unitCount);

    }

private:
    int unitCount = 0;
    std::shared_ptr<Rule> rule;
    int resume{};
    std::unique_ptr<Interface> interface;
};

#endif // GAME_H
