#pragma once
#include "Strategy.h"

class Neutral{

private:
	char neutral_name;
	Context context;
public:
	int damage_buff, armor_buff, speed_buff;
	Neutral() {
		neutral_name = '0';
		damage_buff, armor_buff, speed_buff = 0;
	};
	void setType(char a) {
		neutral_name = a;
	}
	char getType() {
		return neutral_name;
	}
	void use(Unit *a) {
		if (a->getType() == 'i') context.setStrategy(new WarriorsStrategy, damage_buff, armor_buff, speed_buff, a);
		else if (a->getType() == 'a') context.setStrategy(new ArchersStrategy, damage_buff, armor_buff, speed_buff, a);
		else if (a->getType() =='c') context.setStrategy(new CavalryStrategy, damage_buff, armor_buff, speed_buff, a);
	}
	~Neutral() {

	};

};
class ArmorKit : public Neutral {

public:
	ArmorKit() {
		this->setType('A');
		this->armor_buff = 5;
		//std::cout << "Найдена улучшенная броня? Использовать?y/n\n";

	};

	~ArmorKit() {};

};

class WeaponKit : public Neutral {


public:
	WeaponKit() {
		this->setType('W');
		this->damage_buff = 5;
		//std::cout << "Найдена улучшенный боеприпасы? Использовать?y/n\n";
	};
	~WeaponKit() {};
};

class SpeedBoost : public Neutral {
public:
	SpeedBoost() {
		this->setType('S');
		this->speed_buff = 3;
	};
	
	~SpeedBoost() {};
};
class LegendaryItem : public Neutral {
public:
	LegendaryItem() {
		this->setType('L');
		this->speed_buff = 9;
		this->armor_buff = 10;
		this->damage_buff = 10;
	};

	~LegendaryItem() {};
};
