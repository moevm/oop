#pragma once

class Unit {

public:

	int x, y;
	char id;
	int damage, armor, speed;

	Unit() {};

	Unit(int _x, int _y) : x(_x), y(_y){};

	void changePos(int dx, int dy) {

		x = x + dx;
		y = y + dy;
	}

	char getid() 
	{
		return id;
	}
	int getx()
	{
		return x;
	};
	int gety()
	{
		return y;
	}

	~Unit() {

	};

};

class Warrior : public  Unit {

public:

	Warrior() {

		this->armor = 10;
		this->damage = 8;
		this->speed = 1;

	};
	~Warrior() {

	};

};

class Swordman : public Warrior {

public:

	Swordman() {

		this->damage = 5;
		this->id = '1';
	}
	~Swordman() {

	};
};

class Spearman : public Warrior {

public:

	Spearman() {

		this->damage = 7;
		this->id = '2';

	};
	~Spearman() {

	};

};

class Archer : public Unit {

public:

	Archer() {

		this->armor = 7;

	}
	~Archer() {

	}
};

class Slinger : public Archer {

public:

	Slinger() {

		this->id = '3';
		this->damage = 10;
		this->speed = 3;

	};
	~Slinger() {

	};

};

class Bowman : public Archer {

public:

	Bowman() {

		this->id = '4';
		this->damage = 12;
		this->speed = 2;


	};
	~Bowman() {

	};
};

class Cavalry : public Unit {

public:

	Cavalry() {
	
	};
	~Cavalry() {

	};

};

class LightCavalry : public Cavalry {

public:

	LightCavalry() {

		this->id = '5';
		this->speed = 5;
		this->armor = 8;
		this->damage = 12;

	};
	~LightCavalry() {

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
	~HeavyCavalry() {

	};

};

