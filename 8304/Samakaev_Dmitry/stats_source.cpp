#include "stats_source.h"

void Hp::change(size_t new_hp)
{
	hp = new_hp;
}

size_t Hp::get()
{
	return hp;
}

void Armor::change(size_t new_armor)
{
	armor = new_armor;
}

size_t Armor::get()
{
	return armor;
}

void Damage::change(size_t new_damage) {
	damage = new_damage;
}

size_t Damage::get() {
	return damage;
}

size_t Coordinates::get_x()
{
	return x;
}

size_t Coordinates::get_y()
{
	return y;
}

bool Coordinates::change_coordinates(size_t new_x, size_t new_y)
{
	x = new_x;
	y = new_y;

	return false;
}
