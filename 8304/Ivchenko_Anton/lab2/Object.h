#pragma once
#include "Neutral.h"
class Object {

private:
	char obj_name;
	Unit* unit;
	Neutral* ntr;
	bool availability;

public:

	Object() { obj_name = '0'; unit = nullptr; ntr = nullptr; };

	void SetUnit(Unit *a) {
		 unit = a;
	};
	void RemoveUnit() {
		unit = nullptr;
	}
	void SetObj(char a) {
		obj_name = a;
	}
	Unit* getUnit() {
		return unit;
	};
	char getObj() {
		return obj_name;
	};
	Neutral *getNeutral() {
		return ntr;
	}
	void setNeutral(Neutral *a) {
		ntr = a;
	}
	void useNeutral () {
		if (ntr->getType() != '0') {
			ntr->use(unit);
		}
	}
	void SetAvailability(bool b) {
		this->availability = b;
	}
	bool IsAvailable() {
		return this->availability;
	}
	~Object() {};

};

class Base : public  Object {

private:

	int x, y;
	int quantity, q_max, hp;

public:

	Base(int _x, int _y) :x(_x), y(_y) {
		this->SetObj('B'); quantity = 0, q_max = 10, hp = 100;
	};

	Swordman* createSwordman() {
		if (quantity < q_max) {
			Swordman* swordman = new Swordman;
			quantity++;
			swordman->setCoordinats(0, 2);
			return swordman;
		}
		else return nullptr;
	}
	Spearman* createSpearman() {
		if (quantity < q_max) {
			Spearman* spearman = new Spearman;
			quantity++;
			spearman->setCoordinats(1, 1);
			return spearman;
		}
		else return nullptr;
	}
	Bowman* createBowman() {
		if (quantity < q_max) {
			Bowman* bowman = new Bowman;
			quantity++;
			bowman->setCoordinats(1, 1);
			return bowman;
		}
		else return nullptr;
	}
	Slinger* createSlinger() {
		if (quantity < q_max) {
			Slinger* slinger = new Slinger;
			quantity++;
			slinger->setCoordinats(1, 1);
			return slinger;
		}
		else return nullptr;
	}
	LightCavalry* createLC() {
		if (quantity < q_max) {
			LightCavalry* lc = new LightCavalry;
			quantity++;
			lc->setCoordinats(1, 1);
			return lc;
		}
		else return nullptr;
	}
	HeavyCavalry* createHC() {
		if (quantity < q_max) {
			HeavyCavalry* hc = new HeavyCavalry;
			quantity++;
			hc->setCoordinats(1, 1);
			return hc;
		}
		else return nullptr;
	}
	void printBaseCondition() {
		std::cout << "\nBase condition:\nHp: " << hp << "\nCurreant unit quantity: " << quantity << "\nMax unit quantity: " << q_max << std::endl;
	}
	void deleteUnit(Unit* a) {
		a->~Unit();
		quantity--;

	};


	~Base() {};

};


class Landscape : public Object {

public:

	Landscape() {

	};
	void SetType(char a) {
		this->SetObj(a);


	}

	void speedChange(int d, Unit* a) {
		Atributes* new_c = new Atributes(a->getCharactresistics()->getDamage()->getDamageValue(), a->getCharactresistics()->getArmor()->getArmorValue(), a->getCharactresistics()->getSpeed() + d);
		a->changeCharactresistics(new_c);
	}
	void attackChange(int d, Unit* a) {
		Atributes* new_c = new Atributes(a->getCharactresistics()->getDamage()->getDamageValue() + d, a->getCharactresistics()->getArmor()->getArmorValue(), a->getCharactresistics()->getSpeed());
		a->changeCharactresistics(new_c);
	}
	~Landscape() {

	};
};
class Lake : public Landscape {

public:

	Lake() {
		this->SetType('~');
		this->SetAvailability(0);
		//if (getUnit() != nullptr) {
		//	getUnit()->~Unit();
		//}
	}
	~Lake() {

	};
};

class Mountain : public Landscape {

public:

	Mountain() {
		this->SetType('^');
		this->SetAvailability(0);

	}
	~Mountain() {

	};
};

class Plain : public Landscape {

public:

	Plain() {
		this->SetType(' ');
		this->SetAvailability(1);
		if (getUnit() != nullptr) {
			if (getUnit()->getType() == '3') speedChange(2, getUnit());
		}

	}
	~Plain() {

	};
};

class Forest : public Landscape {

public:

	Forest() {
		this->SetType('#');
		this->SetAvailability(1);
		if (getUnit() != nullptr) {
			if (getUnit()->getType() == '3') speedChange(-1, getUnit());
			if (getUnit()->getid() == '2') attackChange(-1, getUnit());
		}

	}
	~Forest() {

	};
};
