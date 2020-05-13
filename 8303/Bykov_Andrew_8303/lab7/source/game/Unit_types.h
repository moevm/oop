#pragma once
#include "Unit.h"

class EmptyUnit : public Unit {
public :
	EmptyUnit();
	bool update() { return false; };
};

class Infantry : public Unit {
public:

	Infantry(Component *n = 0);
};
class Berserks : public Infantry{
public:
	Berserks(int N, Component *n = 0);
	bool volunteer();
};
class Spearmen : public Infantry {
public:
	Spearmen(int N, Component *n = 0);
	bool volunteer();
};

class Archers : public Unit {
public:

	Archers(Component *n = 0);
};
class LongShooters : public Archers {
public:
	LongShooters(int N, Component *n = 0);
	bool volunteer();
};
class Hunters : public Archers {
public:
	Hunters(int N, Component *n = 0);
	bool volunteer();
};

class Cavalry : public Unit {
public:

	Cavalry(Component *n = 0);
}; 
class Ulans : public Cavalry {
public:
	Ulans(int N, Component *n = 0);
	bool volunteer();
};
class Cuirassiers : public Cavalry {
public:
	Cuirassiers(int N, Component *n = 0);
	bool volunteer();
};

class WaterBerserks : public Berserks
{
public:
	WaterBerserks(int N, Component *n = 0) : Berserks(N, n) { setTeam(0); };
};
class FireBerserks : public Berserks
{
public:
	FireBerserks(int N, Component *n = 0) : Berserks(N, n) { setTeam(1); };
};
class WaterSpearmen : public Spearmen
{
public:
	WaterSpearmen(int N, Component *n = 0) : Spearmen(N, n) { setTeam(0); };
};
class FireSpearmen : public Spearmen
{
public:
	FireSpearmen(int N, Component *n = 0) : Spearmen(N, n) { setTeam(1); };
};
class WaterLongShooters : public LongShooters
{
public:
	WaterLongShooters(int N, Component *n = 0) : LongShooters(N, n) { setTeam(0); };
};
class FireLongShooters : public LongShooters
{
public:
	FireLongShooters(int N, Component *n = 0) : LongShooters(N, n) { setTeam(1); };
};
class WaterHunters : public Hunters
{
public:
	WaterHunters(int N, Component *n = 0) : Hunters(N, n) { setTeam(0); };
};
class FireHunters : public Hunters
{
public:
	FireHunters(int N, Component *n = 0) : Hunters(N, n) { setTeam(1); };
};
class WaterUlans : public Ulans
{
public:
	WaterUlans(int N, Component *n = 0) : Ulans(N, n) { setTeam(0); };
};
class FireUlans : public Ulans
{
public:
	FireUlans(int N, Component *n = 0) : Ulans(N, n) { setTeam(1); };
};
class WaterCuirassiers : public Cuirassiers
{
public:
	WaterCuirassiers(int N, Component *n = 0) : Cuirassiers(N, n) { setTeam(0); };
};
class FireCuirassiers : public Cuirassiers
{
public:
	FireCuirassiers(int N, Component *n = 0) : Cuirassiers(N, n) { setTeam(1); };
};




