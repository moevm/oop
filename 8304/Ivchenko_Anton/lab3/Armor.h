#pragma once

class Armor {
private:
	int armor;
public:
	Armor(int a) {
		armor = a;
	};
	int getArmorValue() {
		return armor;
	}
	void setArmor(int a) {
		armor = a;
	}
	int reduceHealth(int d) {
		armor = armor - d;
		return armor;

	}
	~Armor() {};

};
