

#ifndef GameUnits_h
#define GameUnits_h
#include <vector>
class GameMap;
class EnemiesUnits;
class Unit;


class GameUnits{
public:
    int size;
    int type;
    std::vector <Unit*> units;
    GameUnits();
    bool moveUnit(int x, int y, int index, GameMap &gameMap);
    Unit* getUnit(int x, int y);
    void addUnit(Unit* unit, int x, int y, GameMap &map);
    void attack(int index, GameMap &gameMap, EnemiesUnits& enemies);
    void update();
    int changeActiveUnit();
};

class EnemiesUnits: public GameUnits{
public:
    EnemiesUnits(){
        type = -1;
    }
};

class FriendsUnits: public GameUnits{
public:
    FriendsUnits(){
        type = 1;
    }
};


#endif /* GameUnits_h */
