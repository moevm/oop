#include "Base.h"

base::base(int num) {
	number = num;
	hp = feature(200);
	max_units = 3;
	tmp_unit = 0;
	count_units = 0;
	x = 0;
	is_alive = true;
	y = 0;
	name = 30;
	owner = NULL;
	for (int i = 0; i < 3; i++) {
		units[i] = create_unit(get_creature());
		is_unit[i] = true;
	}

}

base::~base() {
	for (int i = 0; i < 3; i++) {
		if(is_unit[i])
			delete(units[i]);
	}

}

void* base::get_owner() { return owner; }

void base::set_owner(void* own) { owner = own; }

void base::set_coords(int xx, int yy) {
	if (xx < 0 || yy < 0) throw except("(base::set_coords) Trying to set base negative coords: ("+to_string(xx)+","+to_string(yy)+")\n");
	x = xx;
	y = yy;
}

int base::set_hp(int new_hp) {
	if (new_hp <= 0) {
		new_hp = 0;
		is_alive = false;
		name = 'X';
	}
	hp.set_tmp(new_hp);
	if (hp.get_tmp() <= 0) return 1;
}

int base::sub_hp(int sub) {
	if(sub > 0) hp.add( -1*sub);
	if (hp.get_tmp() <= 0) {
		set_hp(0);
		return 1;
	} 
}

bool base::is_base_alive(){
	return is_alive;
}

int base::get_hp() {
	return hp.get_tmp();
}

unit* base::get_unit(int i) {
	int f = is_any_alive();
	if (f == -1) return NULL;
	if (i < 0 || i > 2) return units[f];
	if (is_unit[i]) return units[i];
	else return NULL;
}

bool base::is_unit_alive(int i) {
	if (i < 0 || i > 2) return is_unit[0]; //ERROR
	return is_unit[i];

}

int base::get_number() { 
	return number;
}

unit* base::get_tmp_unit() { 
	if(!is_unit[tmp_unit]) return NULL;
	return units[tmp_unit];
}

bool base::set_tmp_unit(int i) {
	if (i < 0 || i > 2) return false;
	if (!is_unit[i]) return false;
	tmp_unit = i;
	return true;
}

int base::is_any_alive() {
	for (int i = 0; i < 3; i++) {
		if (is_unit[i]) return i;
	}
	logger::add("Base number " + to_string(number) + " has no more units alive!\n");
	return -1;
}

int base::how_many_alive() {
	int i = 0;
	for (int j = 0; j < 3; j++) {
		if (is_unit[i])i++;
	}
	return i;

}

int base::get_x() {
	return x;
}

int base::get_y() {
	return y;
}

char base::get_name() {
	return name;
}

void base::set_unit(int x, int y, char name, int hdp, int  hp_max, int armor, int attack, int xp, int xp_level, int level, int i) {
	if (is_unit[i]) delete_unit(i);
	if (x < 0 || y < 0 || hdp <= 0 || i < 0 || i > 2) throw except("(base::set_unit)Something goes wrong with creating unit!\n\tStats: (" + to_string(x)+"," +to_string(y) + ")  hp: " + to_string(hdp) +" at " + to_string(i) +" position in base number "+ to_string(number) + "\n");



	is_unit[i] = true;
	switch (name) {
	case 'c': {
		crow* unit_crow = new crow;
		unit_crow->set_base_nubmer(number);
		unit_crow->set_base(this);
		count_units++;
		unit_crow->set_coords(x, y);
		unit_crow->set_all(hdp, hp_max, armor, attack, xp, xp_level, level);


		units[i] = unit_crow;
		return;
	}
	case 'w': {
		wolf* unit_wolf = new wolf;
		unit_wolf->set_base_nubmer(number);
		unit_wolf->set_base(this);
		count_units++;
		unit_wolf->set_coords(x, y);
		unit_wolf->set_all(hdp, hp_max, armor, attack, xp, xp_level, level);


		units[i] = unit_wolf;
		
		return;
	}
	case 'h': {
		hyena* unit_hyena = new hyena;
		unit_hyena->set_base_nubmer(number);
		unit_hyena->set_base(this);
		unit_hyena->set_coords(x, y);
		unit_hyena->set_all(hdp, hp_max, armor, attack, xp, xp_level, level);


		units[i] = unit_hyena;
		count_units++;
		
		return;
	}
	case 'l': {
		lizard* unit_lizard = new lizard;
		unit_lizard->set_base_nubmer(number);
		unit_lizard->set_base(this);
		count_units++;
		unit_lizard->set_coords(x, y);
		unit_lizard->set_all(hdp, hp_max, armor, attack, xp, xp_level, level);


		units[i] = unit_lizard;
		return;
	}
	case 'd': {
		duck* unit_duck = new duck;
		unit_duck->set_base_nubmer(number);
		unit_duck->set_base(this);
		count_units++;
		unit_duck->set_coords(x, y);
		unit_duck->set_all(hdp, hp_max, armor, attack, xp, xp_level, level);


		units[i] = unit_duck;
		return;
	}
	case 'f': {
		frog* unit_frog = new frog;
		unit_frog->set_base_nubmer(number);
		unit_frog->set_base(this);
		count_units++;
		unit_frog->set_coords(x, y);
		unit_frog->set_all(hdp, hp_max, armor, attack, xp, xp_level, level);


		units[i] = unit_frog;

		return;
	}
			

	}
	is_unit[i] = false;
	throw except("(base::set_unit) Can't create unit with this name: "+to_string(name)+"\n\tit's dosn't match any type-name\n");
}

creature base::get_creature() {
	//srand(time(0));
	int c = rand() % 6;
	switch (c) {
	case 0: return Duck;
	case 1:	return Crow;
	case 2: return Wolf;
	case 3: return Hyena;
	case 4: return Frog;
	case 5: return Lizard;
	}

}

unit* base::create_unit(creature type = Crow) {
	if (count_units >= max_units) {
		cout << "There is maximum count of units alredy!\n";
		return NULL;
	}
	if (type == None) {
		logger::add("Can't create None unit\n");
		throw exception("(base::create_unit) Can't create None-type unit!\n");
		return NULL;
	} // ERROR
	if (!is_alive) return NULL;

	logger::add("Base number "+to_string(number) +" just make new unit-");
	switch (type) {
	case Crow: {
		crow* unit_crow = new crow;
		unit_crow->set_base_nubmer(number);
		unit_crow->set_base(this);
		count_units++;
		logger::add("crow\n");
		return unit_crow;
		break;
	}
	case Wolf: {
		wolf* unit_wolf = new wolf;
		unit_wolf->set_base_nubmer(number);
		unit_wolf->set_base(this);
		count_units++;
		logger::add("wolf\n");
		return unit_wolf;
		break;
	}
	case Hyena: {
		hyena* unit_hyena = new hyena;
		unit_hyena->set_base_nubmer(number);
		unit_hyena->set_base(this);
		count_units++;
		logger::add("hyena\n");
		return unit_hyena;
		break;
	}
	case Lizard: {
		lizard* unit_lizard = new lizard;
		unit_lizard->set_base_nubmer(number);
		unit_lizard->set_base(this);
		count_units++;
		logger::add("lizard\n");
		return unit_lizard;
		break;
	}
	case Duck: {
		duck* unit_duck = new duck;
		unit_duck->set_base_nubmer(number);
		unit_duck->set_base(this);
		count_units++;
		logger::add("duck\n");
		return unit_duck;
		break;
	}
	case Frog: {
		frog* unit_frog = new frog;
		unit_frog->set_base_nubmer(number);
		unit_frog->set_base(this);
		logger::add("frog\n");
		count_units++;
		return unit_frog;
		
		break;
	}

	}

}

int base::create_unit() {
	if (count_units >= max_units) {
		cout << "There is maximum count of units alredy!\n";
		return -1;
	}
	if (!is_alive) return -1;
	
	for (int i = 0; i < 3; i++) {
		if (!is_unit[i]) {
			units[i] = create_unit(get_creature());
			is_unit[i] = true;
			return i;
		}
	
	}
	return -1;

}

int base::delete_unit() {
	for (int i = 0; i < max_units; i++) {
		if (is_unit[i] && (units[i])->get_hp() <= 0 ) {
			delete(units[i]);
			logger::add("Base number " + to_string(number) + " just delete unit\n");
			is_unit[i] = false;
			count_units--;
		}
		
	}
	return -1;
}

int base::delete_unit(int i) {
	if (is_unit[i]) {
		delete units[i];
		is_unit[i] = false;
		count_units--;
	}
	return i;
}

void base::get_info() {

	std::cout << " \t   Your base at (" << x << " ; " << y << ") \n";
	std::cout << " \t   with " << hp.get_tmp() << "\\200 hp\n";
}

bool operator-(base& un, unit* it) {
	if (un.is_alive) logger::add("\tBase number " + to_string(un.number) + " get hit; now it has " + to_string(un.get_hp()) + " hp\n");

	un.sub_hp(it->get_attack() / 2);
	if (un.get_hp() > 0) return false;
	if (!un.is_alive) return true;
	logger::add("Base number " + to_string(un.number) + " is dead!\n");
	un.set_hp(0);
	un.is_alive = false;
	un.name = 'X';
	return true;
}
