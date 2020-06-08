#pragma once
#include <iostream>
#include "Unit.h"
#include "Base.h"
#include "Land.h"
#include "Item.h"
#include "Logger.h"

class field_cell {
private:
	int x;
	int y;
	creature type_unit;
	unit* tmp_unit;
	biome land;
	bool is_bas;
	Item type_item;
	item* tmp_item;
	base* tmp_base;
	

public:
	field_cell(int new_y, int new_x, int new_land);
	void set_unit(unit* new_unit);
	void set_unit_type(creature new_type);
	Item get_item_type();
	int set_item(int c);
	base* get_base();
	item* get_item();
	void delete_item();
	bool is_empty();
	void set_base(base* b);
	int get_x();
	int get_y();

	char get_land_icon();
	int get_land_number();
	biome get_land();
	bool is_base();
	int get_color();
	int get_background();
	creature get_unit_type();
	unit* get_unit();
	void delete_unit();
	
};

class field {
private:
	int x_size;
	int y_size;
	field_cell** map;
	int max_unit;
	int count_units;
	
	int random_land(int y, int x);
public:
	field(int x, int y);
	field();
	field(int x, int y, int** lands);

	~field();
	field_cell* get_cell(int x, int y);
	field_cell* find_empty(int x, int y);
	int get_item_count();
	void move_unit(int x1, int y1, int x2, int y2);
	

	void set_base(int x, int y, base* b);
	
	int get_x_size();
	int get_y_size();
	
	
};

