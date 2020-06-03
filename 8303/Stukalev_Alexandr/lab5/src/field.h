#ifndef FIELD_H
#define FIELD_H

#include "units.h"
#include "landscape.h"
#include "neutralobj.h"
#include "composit.h"
#include "observer.h"
#include "logging.h"

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
private:
    int lengthX;
    int lengthY;
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
    void create_Landscape(int x, int y, char name);
    void createAUnit(char unit);
    void insertAUnit(char unit , int health, int damage, int armor, int x, int y);
    void insertHUnit(char unit , int health, int damage, int armor, int x, int y);
    void createHUnit(char unit);
    void show_Neutral();
    void allUnitsDis();
    void moveAUnit(char wayToMove, Unit*unit);
    void moveHUnit(char wayToMove, Unit*unit);
    void create_ABase(int max_count, int health);
    void create_HBase(int max_count, int health);
    void allNeutral();
    bool getIsMaxCount();
    bool getIsAMaxCount();
    bool getIsHMaxCount();
    bool checkCell(int x, int y);
    bool checkUnit(int x, int y) const;
    bool checkABase(int x, int y);
    bool checkHBase(int x, int y);
    bool checkAleinBase();
    bool checkHumanBase();
    int getX() const;
    int getY() const;
    char getLandscapeName(int, int) const;
    char getNeutralName(int, int) const;
    Unit* getUnit(int x, int y) const;
    Base* getABase();
    Base* getHBase();
    Unit* getAChoosen();
    Unit* getHChoosen();
    Field& operator=(const Field&);
};


class Base: public Observer
{
private:
    int health;
    int x,y;
    int count, max_count;
    char designation;
    Composit* comp_unit;
    HumanArmyFactory hu_army;
    AlienArmyFactory al_army;
    string baseName;
public:
    Base(int max_count, int health, int x, int y, string baseName);
    Base(int max_count , int count, int health, int x, int y, string baseName);
    void remove_unit(Unit* unit);
    void create_unit(Field* field,char name, char army);
    void insert_unit(Field* field,char name, char army , int health, int damage, int armor, int x, int y);
    void update(Subject* subject);
    void move_unit(Field* field, char c, Unit* unit);
    void attackThis(int n);
    void GameOver();
    int getHealth();
    int getMaxUnits();
    int getCurrUnits();
    int getX();
    int getY();
    string getBaseName();
    bool getIsMaxCount();
    Unit* getAChoosen();
    Unit* getHChoosen();
};
#endif // FIELD_H
