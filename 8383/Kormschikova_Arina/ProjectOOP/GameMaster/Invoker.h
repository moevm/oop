

#ifndef Invoker_h
#define Invoker_h

class Base;
class GameUnits;
class GameMap;
class FriendsUnits;
class EnemiesUnits;
class Unit;
class Command;
class HelpHandler;
class BaseControlHandler;
class ChangeUnitHandler;
class MoveHandler;
class AttackHandler;

class Invoker{
public:
    Command* command;
    
    GameMap *map;
    FriendsUnits* units;
    EnemiesUnits* enemies;
    Base* base;
    int* index;
    bool death;
    HelpHandler* helpMePleaseH;
    BaseControlHandler* baseH;
    ChangeUnitHandler* changeH;
    MoveHandler* moveH;
    AttackHandler* attackH;
    Invoker(GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base* base, int* index);
    void invokerCycle(char request);
};
    

#endif /* Invoker_h */
