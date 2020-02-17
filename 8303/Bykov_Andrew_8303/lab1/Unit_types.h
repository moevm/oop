#pragma once
#include "Unit.h"
#include "Field.h"

class Infantry : public Unit {
public:

	Infantry();
};

class Berserks : public Infantry{
public:
	Berserks(int N);
	void place(Field &field);
};

class Spearmen : public Infantry {
public:
	Spearmen(int N);
	void place(Field &field);
};


class Archers : public Unit {
public:

	Archers();
};

class Fire_Archers : public Archers {
public:
	Fire_Archers(int N);
	void place(Field &field);
};
class Hunters : public Archers {
public:
	Hunters(int N);
	void place(Field &field);
};

class Cavalry : public Unit {
public:

	Cavalry();
}; 

class Ulans : public Cavalry {
public:
	Ulans(int N);
	void place(Field &field);
};
class Cuirassiers : public Cavalry {
public:
	Cuirassiers(int N);
	void place(Field &field);
};
