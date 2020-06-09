#pragma once
#include <iostream>
#include "Base.h"


class player {
	base* my;
	string name;
public:
	player(string new_name, int bn);
	~player();
	base* get_base();
	unit* get_tmp_unit();
	void set_tmp_unit(int i);
	string get_name();
	int is_any_alive();
	void set_base(base* b);
};
