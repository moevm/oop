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
    Base* base = nullptr;
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
public:
    Field(int lengthY, int lengthX);
    Field(const Field& ref_obj);
    Field(Field&& ref_obj);
    ~Field();
    void insert_Unit(Unit* obj);
    void remove_Unit(Unit* obj);
    void move_Unit(Unit* obj, int x, int y);
    void print_field() const;
    Base* create_Base(int max_count, int health);
    void create_Landscape();
    void show_Landscape();
    void create_Neutral(int x, int y, char name);
    void show_Neutral();
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
    Base(int max_count, int health);
public:
    void remove_unit(Unit* unit);
    void create_unit(Field* field,char name, char army);
    void update(Subject* subject);
};
#endif // FIELD_H
