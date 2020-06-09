#pragma once

class feature {
	int tmp;
	int max;
public:
	feature();
	feature(int n_max);
	int get_tmp();
	int get_max();
	void set_tmp(int n_tmp);
	void set_max(int n_max);
	bool add(int num);
};

class ulevel {
	int tmp_xp;
	int tmp_level;
	int xp_for_next_level;
	void new_level();
public:
	ulevel();
	bool plus_xp(int xp);
	int get_tmp_level();
	int get_xp_for_next_level();
	int get_tmp_xp();
};
