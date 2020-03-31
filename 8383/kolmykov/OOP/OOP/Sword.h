#pragma once
#include "Weapon.h"
class Sword :
	public Weapon
{
public:
	Sword();
	Sword(const Sword& other);
	~Sword();
};

