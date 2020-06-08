#ifndef ARCHER
#define ARCHER
#include "unit.h"

class Archer : public Unit {
public:
	Archer() = default;
	virtual void Mapping(int, int, int) = 0;
	virtual int Move(int, int) = 0;
	virtual int Attack(int**, int) = 0;
	virtual void GetDamage(int) = 0 ;
};
#endif