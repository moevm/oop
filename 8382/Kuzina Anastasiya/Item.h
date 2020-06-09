#pragma once
enum Item {Non, Exp, Pill, Zatochka, Rand};

class item {
protected:
	char name;
	int effect;
public:
	item();
	int get_effect();
	char get_name();
};


// опыт, хил, рандомная таблетка, заточкa


class exp_bottle :public item {
public: 
	exp_bottle();

};

class hp_pill : public item {
public:
	hp_pill();

};

class zatochka :public item {
public:
	zatochka();
};

class rpill : public item {
public:
	rpill();

};