#pragma once
#include <iostream>
#include <conio.h>
#include "Unit.h"
#include "Feature.h"
#include "Logger.h"
#include "Exept.h"
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
using namespace std;

	unit::unit() {
		base_number = -1;
		ubase = NULL;
		hp = feature(10);
		armor = feature(10);
		attack = feature(10);
		level = ulevel();
		name = 'u';
		x = -1;
		y = -1;
		return;
	}
	void unit::set_info(int new_hp, int new_attack, int new_armor) {
		hp = feature(new_hp);
		attack = feature(new_attack);
		armor = feature(new_armor);
	}
	void unit::get_info() {
		cout << "\tName: " << name << "(" << x << ", " << y << ")\n";
		cout << "\tHP: " << hp.get_tmp() << " Attack : " << attack.get_tmp() << " Armor : " << armor.get_tmp() << endl; 
		cout << "\tLevel : " << level.get_tmp_level() <<"    Xp: "<< level.get_tmp_xp() << "    Xp for level up: " << level.get_xp_for_next_level() << "\n";
	}
	void unit::set_hp(int nhp) {
		hp.set_tmp(nhp);
	}
	bool unit::add_hp(int num) {
		if (hp.add(num)) {
			return true;
		}
		return false;
	}
	void unit::add_armor(int num) {
		armor.add(num);
	}
	void unit::add_attack(int num) {
		attack.add(num);
	}
	void unit::add_xp(int num) {
		if (level.plus_xp(num)) {
			hp.set_max(hp.get_max() + 10);
			hp.set_tmp(hp.get_tmp() + 5);
			armor.set_max(armor.get_max() + 2);
			attack.set_max(attack.get_max() + 2);
		}
	}
	void unit::set_type(creature t) { 
		if (t == None) throw except("(unit::set_type) You can't set unit None-type\n");
		type = t;
	}
	void unit::set_base_nubmer(int t) { base_number = t; }
	int unit::get_base_number() { return base_number; }
	void unit::set_base(void* bs) { ubase = bs; }
	void* unit::get_base() { return ubase;   }

	void unit::set_name(char new_name) {
		name = new_name;
	}
	void unit::set_coords(int new_x, int new_y) {
		if (new_x < 0 || new_y < 0) throw except("Trying to set unit negativ coords: ("+to_string(x)+","+to_string(y)+")\n");
		x = new_x;
		y = new_y;
	}
	int unit::get_hp() { return hp.get_tmp(); }
	int unit::get_armor() { return armor.get_tmp(); }
	int unit::get_attack() { return attack.get_tmp(); }
	char unit::get_name() { return name; }
	int unit::get_x() { return x; }
	creature unit::get_type() { return type; }
	int unit::get_y() { return y; }

	char unit::beware() {
		switch (name){
		case 'w':
		case 'h': return 126;
		case 'f':
		case 'l': return 94;
		case 'd':
		case 'c': return 6;
		}
		throw except("(unit::beware) Incorrect unit name -"+ to_string(name) +"- doesn't match any creature type");
	}

	unit operator+(unit& un, item* it) {
		
		char c = it->get_name();
		if (c == '$')
			un.add_xp(it->get_effect());
		else if (c == 3)
			un.add_hp(it->get_effect());
		else if (c == '*')
			un.add_armor(it->get_effect());
		else if (c == 4)
			un.add_attack(it->get_effect());
		else throw except("(unit::operatior+) Unexpected item name -"+ to_string(c)+", doesn't match any item types\n");
		logger::add("\t"+un.get_u_info()+"find some item\n");
		return un;
	}

	unit operator-(unit& un, unit* it) {
		logger::add("\tfight between "+ un.get_u_info() + " and " + it->get_u_info() + "\n");
		int att = it->get_attack();
		int arr = un.get_armor();
		it->add_xp(10);
		un.add_armor(-1);
		if (arr > att) {
			it->add_hp(-1);
			logger::add("\t\t" + it->get_u_info() + " is weaker and get -1 hp\n");
			return un;
		}
		logger::add("\t\t" + un.get_u_info() + " is weaker and get " + to_string(arr - att)+" hp\n");
		un.add_hp(arr - att);
		return un;
	}

	int unit::set_all(int hdp, int  hp_max, int aror, int atack, int x, int xp_level, int lvel) {
		
		hp.set_tmp(hdp);
		hp.set_tmp(hp_max);
		armor.set_tmp(aror);
		attack.set_tmp(atack);

		while (level.get_tmp_xp() != x || level.get_tmp_level() != lvel) {
			level.plus_xp(1);
			if (level.get_tmp_level() > lvel) return 1;
		}
	
	
		return 1;
	}

	int unit::get_hp_max() { return hp.get_max(); }
	int unit::get_armor_max() { return armor.get_max(); }
	int unit::get_attack_max() { return attack.get_max(); }
	int unit::get_level() { return level.get_tmp_level(); }
	int unit::get_xp() { return level.get_tmp_xp(); }
	int unit::get_xp_for_next_level() { return level.get_xp_for_next_level(); }
	string unit::get_u_info() {
		string inf = " ";
		inf.push_back(name);
		inf = inf + " base-" + to_string(base_number) + " ";
		inf = inf + "(" + to_string(x) + "," + to_string(y) + ")";
		return inf;
	
	}


	mammal::mammal():unit(){
		set_name('m');
	}

	wolf::wolf() :mammal() {
		set_name('w');
		set_info(15, 5, 5);
		set_type(Wolf);
	}

	hyena::hyena() :mammal() {
		set_name('h');
		set_info(20, 2, 20);
		set_type(Hyena);
	}

	bird::bird() :unit() {
		set_name('b');
	}

	crow::crow() :bird() {
		set_name('c');
		set_info(15, 5, 15);
		set_type(Crow);
	}

	duck::duck() : bird() {
		set_name('d');
		set_info(20, 10, 5);
		set_type(Duck);
	}

	amphibia::amphibia() :unit() {
		set_name('a');
	}

	frog::frog() :amphibia() {
		set_name('f');
		set_info(5, 5, 10);
		set_type(Frog);
	}

	lizard::lizard() :amphibia() {
		set_name('l');
		set_info(10, 10, 5);
		set_type(Lizard);
	}

