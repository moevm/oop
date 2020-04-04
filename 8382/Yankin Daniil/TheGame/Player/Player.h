#pragma once

#include <cstdint>
#include <set>

class IUnit;
class Base;
class NeutralContext;


class Player
{
    friend class Game;
    friend class GameFacade;

public:
    Player(uint8_t color);
    ~Player();
    uint8_t getColor();

    void addUnit(IUnit* unit);
    void removeUnit(IUnit* unit);

    void addBase(Base* base);
    void removeBase(Base* base);

private:
    std::set <IUnit*>* getUnitSet();
    std::set <Base*>* getBaseSet();

    uint8_t color;

    std::set <IUnit*> unitSet;
    std::set <Base*> baseSet;
};


enum PlayerColors {
    PLAYER_BLUE,
    PLAYER_RED,
    PLAYER_GREEN
};
