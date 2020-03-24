#pragma once

class Unit {

public:

	char id;
	int damage;
	int armor;
	int speed;

};

class Warrior : public Unit {

public:

	Warrior() {

		this->armor = 10;
		this->damage = 8;
		this->speed = 1;

	};

};

class Swordman : public Warrior {


public:

	Swordman() {
		this->damage = 5;
		this->id = '1';
	}
};

class Spearman : public Warrior {

public:

	Spearman() {

		this->damage = 7;
		this->id = '2';

	};
};

class Archer : public Unit {

public:

	Archer() {

		this->armor = 7;

	}
};

class Slinger : public Archer {

public:

	Slinger() {

		this->id = '3';
		this->damage = 10;
		this->speed = 3;

	};
};

class Bowman : public Archer {

public:

	Bowman() {

		this->id = '4';
		this->damage = 12;
		this->speed = 2;


	};
};

class Cavalry : public Unit {

public:

	Cavalry() {};
};

class LightCavalry : public Cavalry {

public:

	LightCavalry() {

		this->id = '5';
		this->speed = 5;
		this->armor = 8;
		this->damage = 12;

	};
};

class HeavyCavalry : public Cavalry {

public:

	HeavyCavalry() {

		this->id = '6';
		this->speed = 3;
		this->armor = 10;
		this->damage = 15;

	};
};
