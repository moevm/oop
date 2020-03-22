#pragma once
#include "Weapon.h"
class StinkingBody :
	public Weapon
{
public:
	StinkingBody();
	StinkingBody(const StinkingBody& other);
	~StinkingBody();
};

