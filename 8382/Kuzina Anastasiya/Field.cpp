#pragma once
#include <iostream>
using namespace std;
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include "Base.h"
#include "Field.h"

	field_cell::field_cell(int new_y, int new_x, int new_land) {
		is_bas = false;
		tmp_base = NULL;
		if (new_x < 0 || new_y < 0) throw except("(field_cell::fild_cell) Trying to create cell with negative coords: ("+to_string(new_x)+","+to_string(new_y)+")\n");
		x = new_x;
		y = new_y;
		type_unit = None;
		int c = rand() % 50;
		if (c <= 5 || c > 12) {
			type_item = Non;
			tmp_item = NULL;
		}
		else if (c > 5 && c < 8) {
			type_item = Exp;
			tmp_item = new exp_bottle();
		}
		else if(c > 7 && c < 10){
			type_item = Pill;
			tmp_item = new hp_pill();
		}
		else if (c > 9 && c < 12) {
			type_item = Zatochka;
			tmp_item = new zatochka();
		}
		else if (c > 11 && c < 13) {
			type_item = Rand;
			tmp_item = new rpill();
		}
		switch (new_land) {
		case 0: {
			land = sunflower();
			break;
		}
		case 1:{
			land = lake();
			break;
		}
		case 2: {
			land = mountain();
			break;
		}
		case 3: {
			land = forest();
			break;
		}
		default:
			throw except("(filed_cell::field_cell) Cell("+to_string(x)+","+to_string(y)+") Wrong landscape number! Expected for 0 to 3, get: "+to_string(new_land)+"\n");
		}
	}
	void  field_cell::set_unit(unit* new_unit) {
		tmp_unit = new_unit;
		type_unit = new_unit->get_type();
		new_unit->set_coords(x, y);
	}
	int field_cell::set_item(int c) {
		if (c == 1) {
			type_item = Exp;
			tmp_item = new exp_bottle();
		}
		else if (c == 2) {
			type_item = Pill;
			tmp_item = new hp_pill();
		}
		else if (c == 3) {
			type_item = Zatochka;
			tmp_item = new zatochka();
		}
		else if (c == 4) {
			type_item = Rand;
			tmp_item = new rpill();
		}
		else throw except("(field_cell::set_item) Cell(" + to_string(x) + "," + to_string(y) + ") Incorrect item number, expected from 1 to 4, get: "+to_string(c)+"\n");
		return c;
	}
	bool field_cell::is_empty() {
		int tes = 1;
		if (type_unit != None) tes = 0;
		if (type_item != Non) tes = 0;
		if (is_bas) tes = 0;

		return tes;
	}
	void  field_cell::set_unit_type(creature new_type) {
		type_unit = new_type;
	}
	int  field_cell::get_x() {
		return x;
	}
	int  field_cell::get_y() {
		return y;
	}
	bool field_cell::is_base() { return is_bas;}
	Item field_cell::get_item_type() {
		return type_item;
	}
	item* field_cell::get_item() {
		if (type_item == Non) throw except("(field_cell::get_item) Cell(" + to_string(x) + "," + to_string(y) + ") Trying to get item, but item-type is None\n");
		return tmp_item;
	}
	void field_cell::delete_item() {
		if (type_item != Non) {
			delete(tmp_item);
			type_item = Non;
		}
	}
	void field_cell::set_base(base* b) {
		if (is_bas) throw except("(field_cell::set_base) Cell(" + to_string(x) + "," + to_string(y) + ") There is alredy base! Can't rewrite\n");
		tmp_base = b;
		is_bas = true;
		//ERROR
	}
	base* field_cell::get_base() { return tmp_base; }

	char  field_cell::get_land_icon() {
		return land.get_icon();
	}
	int field_cell::get_color() {
		return land.get_color();
	}
	int field_cell::get_land_number() {
		if (get_land_icon() == 126) return 1;
		if (get_land_icon() == 15) return 0;
		if (get_land_icon() == 6) return 3;
		if (get_land_icon() == 94)return 2;
	}
	biome field_cell::get_land() {
		return land;
	}
	int field_cell::get_background() {
		return land.get_background();
	}

	creature  field_cell::get_unit_type() {
		return type_unit;
	}
	unit* field_cell::get_unit() {
		
		return tmp_unit;
	}
	void  field_cell::delete_unit() {
		tmp_unit = NULL;
		set_unit_type(None);
		return;
	}
	


	field::field(int x, int y) {
		if (x <= 0 || y <= 0) throw except("(field::field)Field can't be created with this parameters: ("+to_string(x)+","+to_string(y)+")\n");
		logger::add("Field (" +to_string(x) + "," +to_string(y)+") was created\n");
		max_unit = y * x / 3;
		count_units = 0;
		x_size = x;
		y_size = y;
		map = (field_cell**)malloc(sizeof(field_cell*) * y_size);

		for (int i = 0; i < y_size; i++) {
			map[i] = (field_cell*)malloc(sizeof(field_cell) * x_size);

			for (int j = 0; j < x_size; j++)
				map[i][j] = field_cell(i, j, random_land(i, j));
		
		}
		return;
	}
	int field::random_land(int y, int x) {
		if(x < 0 || y < 0) throw except("(field::random_land) Can't return random land with this coords (" + to_string(x) + "," + to_string(y) + ")\n");
		int r = 1;
		if (x == 0) {
			if (y == 0) {
				return rand() % 4;
			}
			else {
				r = rand() % 3;
				if (r) return  rand() % 4;
				else return map[y - 1][x].get_land_number();
			}
		}
		else {
			r = rand() % 2;
			if (r) return  rand() % 4;
			else return map[y][x-1].get_land_number();
		}
		return 0;
	}
	field_cell* field::get_cell(int x, int y) {
		if (x < 0 || y < 0 || x>=x_size ||y >= y_size) throw except("(field::get_cell)Can't return field cell["+to_string(x)+","+to_string(y)+"]\n");
		else return &(map[y][x]);
	}
	
	void field::set_base(int x, int y, base* b) {
		if (x < 0 || y < 0) throw except("(field::set_base)Can't set base at cell[" + to_string(x) + "," + to_string(y) + "]\n");
		map[y][x].set_base(b);
	}
	field_cell* field::find_empty(int x, int y) {
		int s = 50000;
		int m = 0;
		field_cell* tsmp;
		int xx = -1, yy = -1;
		for (int i = 0; i < y_size; i++) {
			for (int j = 0; j < x_size; j++) {
				if (map[i][j].is_empty()) {
					m = (x - j)* (x - j) + (y- i)* (y - i);
					if (m < s) {
						s = m;
						xx = j;
						yy = i;
					}
				}
			}
		}
		if (xx < 0 || yy < 0) throw except("(field::find_empty) Field has no empty cells!\n");
		return &(map[yy][xx]);
	}
	void field::move_unit(int x1, int y1, int x2, int y2) {

		if (y1 < 0 || y2 < 0 || x1 < 0 || x2 < 0) return;
		if (y1 >= y_size || y2 >= y_size || x1 >= x_size || x2 >= x_size)  return;

		if (map[y1][x1].get_unit_type() == None) {
			logger::add("No unit at (" + to_string(x1) + "," + to_string(y1) + "), move denyed\n");
			cout << "There is no unit!\n";
			throw except("(field::move_unit) Can't move unit from (" + to_string(x1) + "," + to_string(y1) + ") There is no unit!\n");
			return;
		}
		base* bb;
		logger::add("unit"+ map[y1][x1].get_unit()->get_u_info() +"trying to move to (" + to_string(x2) + "," + to_string(y2)+")\n");
		if (map[y2][x2].get_unit_type() != None) {
			bb = (static_cast<base*>(map[y2][x2].get_unit()->get_base()));
				logger::add("  but can't: there is unit already:" + map[y2][x2].get_unit()->get_u_info() + "\n");
			if (map[y1][x1].get_unit()->get_base_number() == map[y2][x2].get_unit()->get_base_number()) {
				logger::add("\t and it's his bro!");
			}
			else
				*(map[y2][x2].get_unit()) - map[y1][x1].get_unit();

			if (map[y2][x2].get_unit()->get_hp() <= 0) {
				int i = (bb)->delete_unit();
				map[y2][x2].delete_unit();
				if (i != -1) {
					find_empty(bb->get_x(), bb->get_y())->set_unit(bb->get_unit(i));
				}


			}
		}
		if (map[y2][x2].is_base()) {
			logger::add("  but can't: there base");
			if (map[y1][x1].get_unit()->get_base_number() == map[y2][x2].get_base()->get_number()) {
				logger::add(" and it's unit's home-base\n");
				return;
			}
			else {
				logger::add(" and unit attack it\n");
				*(map[y2][x2].get_base()) - map[y1][x1].get_unit();
				return;
			}
		}
		bb = (static_cast<base*>(map[y1][x1].get_unit()->get_base()));
		if (map[y1][x1].get_unit()->get_hp() <= 0) {
			int i = (bb)->delete_unit();
			map[y1][x1].delete_unit();

		}


		if (!map[y2][x2].is_empty() && map[y2][x2].get_item_type() == Non) return;
		(static_cast<unit*>((map[y1][x1].get_unit()))->set_coords(x2, y2));
		map[y2][x2].set_unit_type(map[y1][x1].get_unit_type());
		map[y2][x2].set_unit(map[y1][x1].get_unit());
		map[y1][x1].set_unit_type(None);
		map[y2][x2].get_unit()->add_hp(map[y2][x2].get_land().get_effect((map[y2][x2].get_unit())));
		
		bb = (static_cast<base*>(map[y2][x2].get_unit()->get_base()));

		if (map[y2][x2].get_item_type() != Non) {
			*(map[y2][x2].get_unit()) + map[y2][x2].get_item();
			map[y2][x2].delete_item();

		}
		if (map[y2][x2].get_unit()->get_hp() <= 0) {
			int i = (bb)->delete_unit();
			map[y2][x2].delete_unit();
			return;
		}
		logger::add("\t unit moves! " + map[y2][x2].get_unit()->get_u_info() +"\n");	
	}

	


	field::field() {}
	int field::get_item_count() {
		int g = 0;
		for (int i = 0; i < y_size; i++) {
			for (int j = 0; j < x_size; j++) {
				if (map[i][j].get_item_type() != Non)
					g++;
			}

		}
		return g;
	}
	field::field(int x, int y, int **lands) {
		if (x <= 0 || y <= 0) throw exception("Field can't be created, y or x is < 0\n");
		max_unit = y * x / 3;
		count_units = 0;
		x_size = x;
		y_size = y;
		map = (field_cell**)malloc(sizeof(field_cell*) * y_size);

		for (int i = 0; i < y_size; i++) {
			map[i] = (field_cell*)malloc(sizeof(field_cell) * x_size);

			for (int j = 0; j < x_size; j++) {
				if (lands[i][j] < 0 || lands[i][j] > 3) throw except("(field::field(**lands)) Wrong land number:" + to_string(lands[i][j])+" for cell ("+to_string(x)+","+to_string(y)+")\n");     
				map[i][j] = field_cell(i, j, lands[i][j]);
				if (map[i][j].get_item_type() != Non)
					map[i][j].delete_item();
			}

		}
		return;
	
	
	}
	int field::get_x_size() { return x_size; }
	int field::get_y_size() { return y_size; }
	field::~field() {
		for (int i = 0; i < y_size; i++) {
			delete(map[i]);
		}
		delete map;
	}