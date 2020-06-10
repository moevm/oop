#pragma once

class Damage {

private:
	int damage;
public:
	Damage(int a) {
		damage = a;
	};
	int getDamageValue() {
		return damage;
	}
	void setDamage(int a) {
		damage = a;
	}
	void raiseDamage(int value) {
		damage = damage + value;
	}
	~Damage() {};
};
