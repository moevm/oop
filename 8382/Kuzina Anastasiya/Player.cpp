#include "Player.h"

player::player(string new_name, int bn) {
	name = new_name;
	my = new base(bn);
	my->set_owner(this);
}

player::~player() {
	delete my;
}

base* player::get_base() { return my; }

unit* player::get_tmp_unit() { return my->get_tmp_unit(); }

void player::set_tmp_unit(int i) {
	my->set_tmp_unit(i);
}

string player::get_name() { return name; }

int player::is_any_alive() {
	return my->is_any_alive();
}

void player::set_base(base* b) {
	delete (my);
	my = b;
	my->set_owner(this);
}