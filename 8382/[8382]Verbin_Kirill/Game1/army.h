#ifndef ARMY
#define ARMY
#include <iostream>
#include "archer.h"
#include "rider.h"
#include "saber.h"

class HeavyRider : public Rider {
public:
	HeavyRider();
	void Mapping(int, int, int);
	int Move(int, int);
	int Attack(int**, int);
	void GetDamage(int);
};

class HeavyArcher : public Archer {
public:
	HeavyArcher();
	void Mapping(int, int, int);
	int Move(int, int) final;
	int Attack(int**, int);
	void GetDamage(int);
};

class HeavySaber : public Saber {
public:
	HeavySaber();
	void Mapping(int, int, int);
	int Move(int, int);
	int Attack(int**, int);
	void GetDamage(int);
};

class LightRider : public Rider {
public:
	LightRider();
	void Mapping(int, int, int);
	int Move(int, int);
	int Attack(int**, int);
	void GetDamage(int);
};

class LightArcher : public Archer {
public:
	LightArcher();
	void Mapping(int, int, int);
	int Move(int, int);
	int Attack(int**, int);
	void GetDamage(int);
};

class LightSaber : public Saber {
public:
	LightSaber();
	void Mapping(int, int, int);
	int Move(int, int);
	int Attack(int**, int);
	void GetDamage(int);
};

#endif

