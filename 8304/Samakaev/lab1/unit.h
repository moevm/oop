#pragma once
#include <iostream>
#include <memory>

class Unit {
public:
	Unit() {
		this->unit_name = ' ';

		this->health = 0;
		this->armor = 0;
		this->attack = 0;

		x = 0;
		y = 0;
	}

	Unit(size_t health, size_t armor, size_t attack, size_t coord_x, size_t coord_y, char name) {
		this->unit_name = name;

		this->health = health;
		this->armor = armor;
		this->attack = attack;

		x = coord_x;
		y = coord_y;
	}

	~Unit() {

	}

	void change_health(int new_health) {
		if (new_health <= 0)
			this->~Unit();
		else health = new_health;
	}

	void change_position(size_t new_x, size_t new_y) {
		x = new_x;
		y = new_y;
	}

	void on_damage_taken(size_t damage) {
		if (damage <= armor)
			change_armor(armor - damage);
		else {
			change_armor(0);
			change_health(health + armor - damage);
		}
	}

	void change_armor(int new_armor) {
		if (new_armor >= 0)
			attack = new_armor;
		else attack = 0;
	}

	void change_attack(int new_attack) {
		if (new_attack >= 0)
			attack = new_attack;
		else attack = 0;
	}

	char get_unit_name() {
		return unit_name;
	}

	size_t get_x() {
		return x;
	}

	size_t get_y() {
		return y;
	}
private:
	char unit_name;

	size_t health;
	size_t armor;
	size_t attack;

	size_t x;
	size_t y;

};

class Vehicle : public Unit {
public:
	Vehicle(size_t health, size_t armor, size_t attack, size_t coord_x, size_t coord_y, char unit_name)
		: Unit(health, armor, attack, coord_x, coord_y, unit_name) {
	}
};

class Plane : public Vehicle {
public:
	Plane(size_t health, size_t armor, size_t attack, size_t coord_x, size_t coord_y, char unit_name)
		: Vehicle(health, armor, attack, coord_x, coord_y, unit_name) {

	}
};

class Tank : public Vehicle {
public:
	Tank(size_t health, size_t armor, size_t attack, size_t coord_x, size_t coord_y, char unit_name)
		: Vehicle(health, armor, attack, coord_x, coord_y, unit_name) {

	}
};

class Humans : public Unit {
public:
	Humans(size_t health, size_t armor, size_t attack, size_t coord_x, size_t coord_y, char unit_name)
		: Unit(health, armor, attack, coord_x, coord_y, unit_name) {

	}
};

class Sniper : public Humans {
public:
	Sniper(size_t health, size_t armor, size_t attack, size_t coord_x, size_t coord_y, char unit_name)
		: Humans(health, armor, attack, coord_x, coord_y, unit_name) {

	}
};

class Medic : public Humans {
public:
	Medic(size_t health, size_t armor, size_t attack, size_t coord_x, size_t coord_y, char unit_name)
		: Humans(health, armor, attack, coord_x, coord_y, unit_name) {

	}
};

class Beasts : public Unit {
public:
	Beasts(size_t health, size_t armor, size_t attack, size_t coord_x, size_t coord_y, char unit_name)
		: Unit(health, armor, attack, coord_x, coord_y, unit_name) {
		beasts_name = unit_name;
	}

	char get_beasts_name() {
		return beasts_name;
	}
private:
	char beasts_name;
};

class Dog : public Beasts {
public:
	Dog(size_t health, size_t armor, size_t attack, size_t coord_x, size_t coord_y, char unit_name)
		: Beasts(health, armor, attack, coord_x, coord_y, unit_name) {

	}
};

class Cat : public Beasts {
public:
	Cat(size_t health, size_t armor, size_t attack, size_t coord_x, size_t coord_y, char unit_name)
		: Beasts(health, armor, attack, coord_x, coord_y, unit_name) {

	}
};