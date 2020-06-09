#pragma once
#include <iostream>
#include <ctime>
#include "Unit.h"
#include "Logger.h"
#include "Exept.h"
//#include "Field.h"

class base {
	int x;
	int y;
	int tmp_unit;
	feature hp;
	char name;
	int number;
	bool is_alive;
	int max_units;
	int count_units;
	unit* units[3];
	bool is_unit[3];
	void* owner;
	unit* create_unit(creature type);
	creature get_creature();


public:
	base(int num);
	~base();
	int how_many_alive();
	int create_unit();
	void set_unit(int x, int y, char name, int hdp, int  hp_max, int armor, int attack, int xp, int xp_level, int level, int i);

	int get_hp();
	void* get_owner();
	void set_owner(void* own);
	void get_info();
	unit* get_tmp_unit();
	bool set_tmp_unit(int i);
	int get_number();
	bool is_base_alive();
	bool is_unit_alive(int i);
	int is_any_alive();
	
	char get_name();
	int get_x();
	int get_y();
	friend bool operator-(base& un, unit* it);
	void set_coords(int xx, int yy);
	int set_hp(int new_hp);
	int sub_hp(int sub);
	unit* get_unit(int i);
	int delete_unit();
	int delete_unit(int i);
};
