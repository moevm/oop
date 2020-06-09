#pragma once
#include <iostream>
#include "Feature.h"
#include "Item.h"
enum creature {Hyena, Wolf, Crow, Duck, Frog, Lizard, None };

class unit {
private:
	feature hp;
	feature armor;
	feature attack;
	ulevel level;
	creature type;
	int base_number;
	void* ubase;

	char name;

	int x;
	int y;

public:
	unit();
	void set_info(int new_hp, int new_attack, int new_armor);
	char beware();
	std::string get_u_info();
	int set_all(int hdp, int  hp_max, int armor, int attack, int xp, int xp_level, int level);
	void get_info();

	int get_base_number();
	void set_base_nubmer(int n);
	void set_base(void* b);
	void* get_base();
	creature get_type();
	void set_type(creature t);
	void set_name(char new_name);
	void set_coords(int new_x, int new_y);
	void set_hp(int nhp);
	bool add_hp(int num);
	void add_attack(int num);
	void add_armor(int num);
	void add_xp(int num);
	friend unit operator+(unit& un, item* it);
	friend unit operator-(unit& un, unit* it);
	int get_hp();
	int get_armor();
	int get_attack();
	int get_hp_max();
	int get_armor_max();
	int get_attack_max();
	int get_level();
	int get_xp();
	int get_xp_for_next_level();

	char get_name();
	int get_x();
	int get_y();

};



class mammal : public unit {
public: mammal();
};
class wolf : public mammal {
public: wolf();
};
class hyena : public mammal {
public: hyena();
};

class bird : public unit {
public:
	bird();
};
class crow : public bird {
public:
	crow();
};
class duck : public bird {
public:
	duck();
};

class amphibia : public unit {
public: amphibia();
};
class frog : public amphibia {
public: frog();
};
class lizard : public amphibia {
public:	lizard();
};
