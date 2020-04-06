#ifndef Command_h
#define Command_h
class Base;
class GameUnits;
class GameMap;
class FriendsUnits;
class EnemiesUnits;
class Unit;

class Command{
public:
    virtual void execute()  = 0;
};

class BaseCommand:public Command{
public:
    Base* baseCont;
    BaseCommand(Base* base): baseCont(base){}
    ~BaseCommand();
    
};

class UnitCommand:public Command{
public:
    FriendsUnits* unitCont;
    UnitCommand(FriendsUnits* unitCont): unitCont(unitCont){}
    ~UnitCommand();
};

class HelpCommand:public Command{
public:
    void execute()  override;
};

class SwitchUnitCommand: public Command{
public:
    
    int* index;
    GameUnits* unitCont;
    SwitchUnitCommand(GameUnits* unitCont, int* index):unitCont(unitCont), index(index){}
    ~SwitchUnitCommand();
    void execute() override;

};
//-------------------------------------//

class MoveCommand: public UnitCommand{
public:
    int x;
    int y;
    int index;
    bool* death;
    GameMap *map;
    MoveCommand(int x, int y, int index, GameMap* map, FriendsUnits* unitCont, bool* death):UnitCommand(unitCont), x(x), y(y), index(index), map(map), death(death){}
    ~MoveCommand();
    void execute()  override;

};

class AttackCommand: public UnitCommand{
public:
    GameMap* map;
    EnemiesUnits* enemies;
    int index;
    AttackCommand(GameMap* map, EnemiesUnits* enemies, FriendsUnits* unitCont, int index):UnitCommand(unitCont), enemies(enemies), map(map), index(index){}
    ~AttackCommand();
    void execute()  override;

};


class CreateUnitInBaseCommand: public BaseCommand{
public:
    CreateUnitInBaseCommand(Base* base):BaseCommand(base){}
    void execute()  override;

};

class SelectUnitInBaseCommand: public BaseCommand{
public:
    
    FriendsUnits* unitCont;
    Unit* newUnit;
    GameMap *map;

    SelectUnitInBaseCommand(FriendsUnits* unitCont, Base* base, GameMap *map):BaseCommand(base), unitCont(unitCont), map(map){}
    ~SelectUnitInBaseCommand();
    void execute()  override;

};

class CreateBaseCommand:public BaseCommand{
public:
    GameMap *map;
    CreateBaseCommand(Base* base, GameMap* map):BaseCommand(base), map(map){};
    ~CreateBaseCommand();
    void execute()  override;

};

class BaseStatCommand: public BaseCommand{
    public:
        BaseStatCommand(Base* base):BaseCommand(base){};
        void execute()  override;

};


#endif /* Command_h */
