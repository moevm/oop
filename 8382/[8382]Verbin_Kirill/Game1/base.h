#ifndef BASE
#define BASE
#include "army.cpp"

class Base {
public:
	int respawn_point;
	int x, y;
	int hp;
	int fraction;
	int* id_array;
	int id, u_id;
	Base(int);
	HeavyArcher* CreateHeavyArcher(int, int);
	HeavyRider* CreateHeavyRider(int, int);
	HeavySaber* CreateHeavySaber(int, int);
	LightArcher* CreateLightArcher(int, int);
	LightRider* CreateLightRider(int, int);
	LightSaber* CreateLightSaber(int, int);
	void GetDamage(int);
	int UnitsCount();
	void UnitDeathControl(int*);
};
#endif 

