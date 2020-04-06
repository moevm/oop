

#ifndef Handler_h
#define Handler_h
class Base;
class GameUnits;
class GameMap;
class FriendsUnits;
class EnemiesUnits;
class Unit;
class Command;

class Handler{
public:
    virtual Handler *setNext(Handler* handler) = 0;
    virtual Command* handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death) = 0;
};

class AbstractHandler: public Handler{
private:
    Handler *nextHandler;
public:
    
    Handler *setNext(Handler* handler) override;
    Command* handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death) override;
};

class AttackHandler: public AbstractHandler{
public:
    Command* handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death) override;
};

class MoveHandler: public AbstractHandler{
    public:

    Command* handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death) override;
};


class ChangeUnitHandler: public AbstractHandler{
    public:
    Command* handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death) override;
    
};
class BaseControlHandler: public AbstractHandler{
    public:
    
    Command* handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death) override;
};
class HelpHandler: public AbstractHandler{
    public:
    Command* handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death) override;
};
#endif /* Handler_h */

