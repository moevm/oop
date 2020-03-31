#include "pch.h"
#include "Archer.h"
#include "Classes.h"


Archer::Archer(int &x, int &y) : Classe_archer('L', 60, 6, 2, 10)
{
	XY.x = x;
	XY.y = y;
}
void Archer::double_shot()
{
}
void Archer::hail_of_arrows()
{
}
void Archer::poison_arrow()
{
}
Archer::~Archer()
{
}

Arbalester::Arbalester(int &x, int &y) : Classe_archer('A', 70, 7, 3, 6)
{
	XY.x = x;
	XY.y = y;
}
void Arbalester::crossbow_shot()
{}
void Arbalester::fire_shot()
{}
void Arbalester::reliable_shot()
{}
Arbalester::~Arbalester()
{}



