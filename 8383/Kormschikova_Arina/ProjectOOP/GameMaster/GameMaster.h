

#ifndef GameMaster_h
#define GameMaster_h
#include "Base.h" //WTF


class GameMap;
class Unit;
class Base;
class EnemiesUnits;
class FriendsUnits;
class Command;
class Invoker;

class GameMaster {
public:
    GameMap* map;
    FriendsUnits* units;
    EnemiesUnits* enemies;
    Base* base;
    Invoker* invoker;
    Command* command;
    void gameCycle();
    void setMap();
    void setEnemies();
    void setBase();
    void baseControl();
    GameMaster();
};



#endif /* GameMaster_h */


