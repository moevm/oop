#include "Unit_types.h"

Infantry :: Infantry() : Unit()
{
	setMaxHealth(100);
}


Berserks::Berserks(int N) : Infantry()
{
	option("Infantry", "Berserks", 80, 40, N);
}
void Berserks::place(Field &field)
{
	field.add_unit("IB", X, Y, number);
}

Spearmen::Spearmen(int N) : Infantry()
{
	option("Infantry", "Spearmen", 80, 40, N);
}
void Spearmen::place(Field &field)
{
	field.add_unit("IS", X, Y, number);
}

Archers :: Archers() : Unit()
{
	setMaxHealth(50);
}

Hunters::Hunters(int N) : Archers()
{
	option("Archers", "Hunt", 80, 40, N);
}
void Hunters::place(Field &field)
{
	field.add_unit("AH", X, Y, number);
}
Fire_Archers::Fire_Archers(int N) : Archers()
{
	option("Archers", "Fire", 80, 40, N);
}
void Fire_Archers::place(Field &field)
{
	field.add_unit("AF", X, Y, number);
}


Cavalry :: Cavalry() : Unit()
{
	setMaxHealth(150);
}

Cuirassiers::Cuirassiers(int N) : Cavalry()
{
	option("Cavalry", "Cuirassiers", 80, 40, N);
	
}
void Cuirassiers::place(Field &field)
{
	field.add_unit("CC", X, Y, number);
}
Ulans::Ulans(int N) : Cavalry()
{
	option("Cavalry", "Ulans", 80, 40, N);
}
void Ulans::place(Field &field)
{
	field.add_unit("CU", X, Y, number);
}
