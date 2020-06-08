#pragma once
#include "stats_source.h"
#include "LandscapeResources.h"
#include "UnitResources.h"

class GameBase;

class Unit {
public:
	Hp hp;
	Armor armor;
	Damage damage;
	unitType type;
	LandscapeEffect landEffect;
	GameBase* my_base = nullptr;
	size_t ind;

	void on_damage_taken(size_t damage_to_take);
	void play_dead();

	char name = '0';

	Unit& operator=(const Unit& unit) {
		hp = unit.hp;
		armor = unit.armor;
		damage = unit.damage;
		name = unit.name;
		return *this;
	}
};