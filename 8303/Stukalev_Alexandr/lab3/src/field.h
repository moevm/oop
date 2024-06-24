#ifndef FIELD_H
#define FIELD_H

#include "units.h"
#include "landscape.h"
#include "neutralobj.h"
#include "composit.h"
#include "observer.h"

using namespace  std;

class Base;
struct Cell
{
    bool is_full = false;
    Unit* unit = nullptr;
    Base* AlienBase = nullptr;
    Base* HumanBase = nullptr;
    Landscape* land;
    Neutral* obj = nullptr;

};

class Field
{
    friend class Base;
private:
    const int lengthX;
    const int lengthY;
    Cell** field = nullptr;
    const int max_object_count;
    int obj_count;
    Base* humanBase;
    Base* alienBase;
public:
    Field(int lengthY, int lengthX);
    Field(const Field& ref_obj);
    Field(Field&& ref_obj);
    ~Field();
    void insert_Unit(Unit* obj);
    void remove_Unit(Unit* obj);
    void move_Unit(Unit* obj, int x, int y);
    void print_field() const;
    void create_Landscape();
    void show_Landscape();
    void create_Neutral(int x, int y, char name);
    void createAUnit(char unit);
    void createHUnit(char unit);
    void show_Neutral();
    void allUnitsDis();
    void moveAUnit(char wayToMove, Unit*unit);
    void moveHUnit(char wayToMove, Unit*unit);
    void allNeutral();
    bool getIsMaxCount();
    bool getIsAMaxCount();
    bool getIsHMaxCount();
    bool checkCell(int x, int y);
    bool checkUnit(int x, int y);
    bool checkABase(int x, int y);
    bool checkHBase(int x, int y);
    bool checkAleinBase();
    bool checkHumanBase();
    int getX() const;
    int getY() const;
    Unit* getUnit(int x, int y);
    void create_ABase(int max_count, int health);
    void create_HBase(int max_count, int health);
    Base* getABase();
    Base* getHBase();
    Unit* getAChoosen();
    Unit* getHChoosen();
};

class Field;

class Base: public Observer
{
    friend class Field;
private:
    int health;
    int x,y;
    int count, max_count;
    char designation;
    Composit* comp_unit;
    HumanArmyFactory hu_army;
    AlienArmyFactory al_army;
    Base(int max_count, int health, int x, int y);
public:
    void remove_unit(Unit* unit);
    void create_unit(Field* field,char name, char army);
    void update(Subject* subject);
    void move_unit(Field* field, char c, Unit* unit);
    void attackThis(int n);
    void GameOver();
    int getHealth();
    int getMaxUnits();
    int getCurrUnits();
    bool getIsMaxCount();
    Unit* getAChoosen();
    Unit* getHChoosen();
};
#endif // FIELD_H
