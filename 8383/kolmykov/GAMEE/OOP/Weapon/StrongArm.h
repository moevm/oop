#pragma once
#include "Weapon.h"
class StrongArm :
	public Weapon
{
public:
	StrongArm();
	StrongArm(const StrongArm& other);
	~StrongArm();
};

