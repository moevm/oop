#pragma once
class Strategy {
public:
	int damage_buff, armor_buff, speed_buff;
	virtual void execute(Unit* a) = 0;
	virtual void operator + (Unit* a) = 0;
};


class WarriorsStrategy: public Strategy{

	void operator + (Unit* a) {
		Atributes* new_c = new Atributes(a->getCharactresistics()->getDamage()->getDamageValue() + (3/5 * damage_buff), a->getCharactresistics()->getArmor()->getArmorValue() + (4/5*armor_buff), a->getCharactresistics()->getSpeed() + (2 / 3 * speed_buff));
		a->changeCharactresistics(new_c);
	}
	void execute(Unit* a) {
		(*this) + a;
	}

};

class ArchersStrategy:public Strategy {

	void operator + (Unit* a) {
		Atributes* new_c = new Atributes(a->getCharactresistics()->getDamage()->getDamageValue() + (4/5 * damage_buff), a->getCharactresistics()->getArmor()->getArmorValue() + (3/5 * armor_buff), a->getCharactresistics()->getSpeed() + (2/3*speed_buff));
		a->changeCharactresistics(new_c);
	}
	void execute(Unit* a) {
		(*this) + a;
	}

};

class CavalryStrategy:public Strategy {

	void operator + (Unit* a) {
		Atributes* new_c = new Atributes(a->getCharactresistics()->getDamage()->getDamageValue() + (2/5 * damage_buff), a->getCharactresistics()->getArmor()->getArmorValue() + (3/5 * armor_buff), a->getCharactresistics()->getSpeed() + speed_buff);
		a->changeCharactresistics(new_c);
	}
	void execute(Unit* a) {
		(*this) + a;
	}
};
class Context {

private:
	Strategy* strategy;
	Unit* unit;
public:
	void setStrategy(Strategy* strat, int a, int b, int c, Unit* unit_) {
		strategy = strat;
		unit = unit_;
		strategy->damage_buff = a;
		strategy->armor_buff = b;
		strategy->speed_buff = c;
	};
	void executeStrategy() {
		strategy->execute(unit);
	};
};
