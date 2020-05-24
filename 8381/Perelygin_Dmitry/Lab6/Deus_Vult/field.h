#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include "forest.h"
#include "plain.h"
#include "mountain.h"
#include "unit.h"
#include <random>
#include <ctime>
class NeturalObjects;
class Base;
class Unit;
class Landscapes;

class Field{

    private:

    protected:
    int unit_count;
    int max_count;
    int size;
    NeturalObjects*** obj_field;
    Base*** base_field;
    Unit*** field;
    int** landscape_view;
    int** obj_view;
    Landscapes*** landscape;
    Landscapes* plains;
    Landscapes* mountains;
    Landscapes* forests;
    public:

    Field(int size, unsigned int maximum_count);


    Field(const class Field &input_field);


    unsigned int get_max_count();

    int get_size();
    void  show_net_obj();

    Unit* get_unit(int x, int y);
    Landscapes* get_landscape(int x, int y);
    int get_obj_type(int x, int y);
    NeturalObjects* get_obj(int x, int y);
    void set_unit_count(int value);
    void set_land(int x, int y, int type);
    void add_netural_obj(class NeturalObjects* net_obj, int x, int y, int num);
    void add_base(class Base* base, int x, int y);
    void clear_obj();
    void clear_unit();
    void show_id();
    void show_base();
    void show_field();
    void show_landscape();
    void delete_unit( int x, int y);

    void save_land();
    void save_obj();

    int add_unit(class Unit *unit,int x, int y,int change_pos = 1);

    ~Field();


};

#endif // FIELD_H
