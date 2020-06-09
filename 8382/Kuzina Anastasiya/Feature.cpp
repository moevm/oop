#include "Feature.h"

feature::feature() {
	max = 1;
	tmp = 1;
}

feature::feature(int n_max) { 
	max = n_max;
	tmp = n_max;
}

int feature::get_tmp() {
	return tmp;
}

int feature::get_max() {
	return max;
}

void feature::set_tmp(int n_tmp) {
	if (n_tmp < 0) n_tmp = 0;
	tmp = n_tmp;
}

void feature::set_max(int n_max) {
	if (n_max <= 0) n_max = 1;
	max = n_max;
}

bool feature::add(int num) { //num может быть < 0
	tmp += num;
	if (tmp > max) tmp = max;
	if (tmp <= 0) return 1; // возвращаем 1, если умер
	return 0;
}


ulevel::ulevel() {
	tmp_xp = 0;
	tmp_level = 1;
	xp_for_next_level = 20;
}

void ulevel::new_level() {
	tmp_xp = 0;
	tmp_level++;
	xp_for_next_level = xp_for_next_level*2;

}

bool ulevel::plus_xp(int xp) {
	tmp_xp += xp;
	if (tmp_xp >= xp_for_next_level) {
		new_level();
		return 1;
	}
	return 0;
}

int ulevel::get_tmp_xp() {
	return tmp_xp;
}

int ulevel::get_tmp_level() {
	return tmp_level;
}

int ulevel::get_xp_for_next_level() {
	return xp_for_next_level;
}