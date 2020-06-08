#pragma once
#include <iostream>

class Hp {
public:
	void change(size_t new_hp);
	size_t get();
private:
	size_t hp = 30;
};

class Armor {
public:
	void change(size_t new_armor);
	size_t get();
private:
	size_t armor = 0;
};

class Damage {
public:
	void change(size_t new_damage);
	size_t get();
private:
	size_t damage = 0;
};

class Coordinates {
public:
	size_t get_x();
	size_t get_y();
	bool change_coordinates(size_t new_x, size_t new_y);

private:
	size_t x;
	size_t y;
};